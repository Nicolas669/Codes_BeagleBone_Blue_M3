/*
 *  motor.h
 * Each channel can support 1.2A continuous
 */

#ifndef _MOTOR_H
#define _MOTOR_H

#include <stdio.h>
#include "gpio.h"
#include "pwm.h"

#define unlikely(x)	__builtin_expect (!!(x), 0)

#define MDIR3B_CHIP		2	//gpio2.8	P8.43
#define MDIR3B_PIN		8	//gpio2.8	P8.43
#define MDIR3A_CHIP		2	//gpio2.9	P8.44
#define MDIR3A_PIN		9	//gpio2.9	P8.44

#define MOT_STBY		0,20	//gpio0.20	P9.41

#define CHANNELS		4

int motor_init_freq(int pwm_frequency_hz);

int motor_free_spin(int ch);

int motor_set(int ch, double duty);


#endif
