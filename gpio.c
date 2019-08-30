/*
 *  gpio.c
 */

#include "gpio.h"

static int chip_fd[CHIPS_MAX];
static int handle_fd[CHIPS_MAX][GPIOHANDLES_MAX];
static int event_fd[CHIPS_MAX][GPIOHANDLES_MAX];

static int __open_gpiochip(int chip)
{
	char buf[MAX_BUF];
	int temp_fd;

	snprintf(buf, sizeof(buf), DEVICE_BASE "%d", chip);
	temp_fd=open(buf,O_RDWR);
	if(temp_fd==-1){
		perror("ERROR opening gpiochip");
		return -1;
	}
	chip_fd[chip]=temp_fd;
	return 0;
}


int gpio_init(int chip, int pin, int handle_flags)
{
	int ret;
	struct gpiohandle_request req;

	// sanity checks
	if(chip<0 || chip>=CHIPS_MAX){
		fprintf(stderr,"ERROR in gpio_init, chip out of bounds\n");
		return -1;
	}
	if(pin<0 || pin>=GPIOHANDLES_MAX){
		fprintf(stderr,"ERROR in gpio_init, pin out of bounds\n");
		return -1;
	}

	// open chip if not opened already
	if(chip_fd[chip]==0){
		if(unlikely(__open_gpiochip(chip))) return -1;
	}

	// request only one pin
	memset(&req,0,sizeof(req));
	req.lineoffsets[0] = pin;
	req.lines = 1;
	req.flags = handle_flags;
	errno=0;
	ret = ioctl(chip_fd[chip], GPIO_GET_LINEHANDLE_IOCTL, &req);
	if(unlikely(ret==-1)){
		perror("ERROR in gpio_init");
		return -1;
	}
	if(req.fd==0){
		fprintf(stderr,"ERROR in gpio_init, ioctl gave NULL fd\n");
		return -1;
	}
	handle_fd[chip][pin]=req.fd;
	return 0;
}


int gpio_set_value(int chip, int pin, int value)
{
	int ret;
	struct gpiohandle_data data;

	// sanity checks
	// sanity checks
	if(chip<0 || chip>=CHIPS_MAX){
		fprintf(stderr,
"ERROR in gpio_set_value, chip out of bounds\n");
		return -1;
	}
	if(pin<0 || pin>=GPIOHANDLES_MAX){
		fprintf(stderr,
"ERROR in gpio_set_value, pin out of bounds\n");
		return -1;
	}
	if(unlikely(handle_fd[chip][pin]==0)){
		fprintf(stderr,
"ERROR, pin %d not initialized yet\n",pin);
		return -1;
	}

	if(value) data.values[0]=1;
	else data.values[0]=0;

	ret = ioctl(
handle_fd[chip][pin], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	if(unlikely(ret==-1)){
		perror("ERROR in gpio_set_value");
		return -1;
	}

	return 0;
}


int gpio_get_value(int chip, int pin)
{
	int ret;
	struct gpiohandle_data data;

	// sanity checks
	if(chip<0 || chip>=CHIPS_MAX){
		fprintf(stderr,
"ERROR in gpio_get_value, chip out of bounds\n");
		return -1;
	}
	if(pin<0 || pin>=GPIOHANDLES_MAX){
		fprintf(stderr,
"ERROR in gpio_get_value, pin out of bounds\n");
		return -1;
	}
	if(unlikely(handle_fd[chip][pin]==0)){
		fprintf(stderr,
"ERROR in gpio_get_value chip %d pin %d not initialized yet\n",chip, pin);
		return -1;
	}

	ret = ioctl(
handle_fd[chip][pin], GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
	if(unlikely(ret==-1)){
		perror("ERROR in gpio_get_value");
		return -1;
	}

	return data.values[0];
}

