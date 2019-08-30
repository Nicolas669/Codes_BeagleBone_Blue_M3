/*
 *  adc.c
 */

#include "adc.h"

static int init_flag = 0; // boolean to check if mem mapped
static int fd[CHANNELS]; // file descriptors for 8 channels


int adc_init(void)
{
	char buf[MAX_BUF];
	int i, temp_fd;
	if(init_flag) return 0;

	for(i=0;i<CHANNELS;i++){
		snprintf(buf, sizeof(buf), IIO_DIR "/in_voltage%d_raw", i);
		temp_fd = open(buf, O_RDONLY);
		if(temp_fd<0){
			perror(
"ERROR in adc_init, failed to open iio adc interface\n");
			fprintf(stderr,
"Perhaps kernel or device tree is too old\n");
			return -1;
		}
		fd[i]=temp_fd;
	}
	init_flag = 1;
	return 0;
}

int adc_cleanup(void)
{
	int i;
	for(i=0;i<CHANNELS;i++){
		close(fd[i]);
	}
	init_flag = 0;
	return 0;
}


int adc_read_raw(int ch)
{
	char buf[8];
	int i;
	//sanity checks
	if(unlikely(!init_flag)){
		fprintf(stderr,
"ERROR in adc_read_raw, please initialize with adc_init() first\n");
		return -1;
	}
	if(unlikely(ch<0 || ch>=CHANNELS)){
		fprintf(stderr,
"ERROR: in adc_read_raw, adc channel must be between 0 & %d\n", CHANNELS-1);
		return -1;
	}
	if(unlikely(lseek(fd[ch],0,SEEK_SET)<0)){
		perror(
"ERROR: in adc_read_raw, failed to seek to beginning of FD");
		return -1;
	}
	if(unlikely(read(fd[ch], buf, sizeof(buf))==-1)){
		perror("ERROR in adc_read_raw, can't read iio adc fd");
		return -1;
	}
	i=atoi(buf);
	if(i>RAW_MAX || i< RAW_MIN){
		fprintf(stderr, 
"ERROR: in adc_read_raw, value out of bounds: %d\n", i);
		return -1;
	}
	return i;
}


double adc_read_volt(int ch)
{
	int raw = adc_read_raw(ch);
	if(raw<0) return -1;
	return raw * 1.8 / 4095.0;
}

