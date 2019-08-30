/*
 *  gpio.h
 */

#ifndef _GPIO_H
#define _GPIO_H

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include "/usr/include/linux/gpio.h"
#include <linux/gpio.h>

#define unlikely(x)	__builtin_expect (!!(x), 0)
#define likely(x)	__builtin_expect (!!(x), 1)

#define DEVICE_BASE "/dev/gpiochip"
#define CHIPS_MAX	6 // up to 6 chip chips, make larger if you want
#define MAX_BUF		64

//handle flags:
#define GPIOHANDLE_REQUEST_INPUT	(1UL << 0)
#define GPIOHANDLE_REQUEST_OUTPUT	(1UL << 1)
#define GPIOHANDLE_REQUEST_ACTIVE_LOW	(1UL << 2)
#define GPIOHANDLE_REQUEST_OPEN_DRAIN	(1UL << 3)
#define GPIOHANDLE_REQUEST_OPEN_SOURCE	(1UL << 4)


int gpio_init(int chip, int pin, int handle_flags);
/*chip : the chip number, /dev/gpiochipX
 *pin : the pin ID
 *handle_flags : the handle flags
*/

int gpio_set_value(int chip, int pin, int value);
/*Sets the value of a GPIO pin when in output mode. 
	Must call gpio_init with the OUTPUT flag first.
 *chip : the chip number, /dev/gpiochipX
 *pin : the pin ID
 *value  0 for off (inactive), nonzero for on (active)
*/

int gpio_get_value(int chip, int pin);
/*Reads the value of a GPIO pin when in input mode or output mode.
	Must call gpio_init first.
 *chip : the chip number, /dev/gpiochipX
 *pin : the pin ID
 */

#endif
