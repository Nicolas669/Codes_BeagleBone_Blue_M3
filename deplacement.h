/*
 *  deplacement.h
 */

#ifndef _DEPLACEMENT_H
#define _DEPLACEMENT_H

#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "motor.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"

#define adc_M3 2
#define GPIO_M3_chip 1
#define GPIO_M3_pin 25


//Variable PWM:
#define PERIODE_PWM 500000    //Periode (500 micros) --> 2KHz

#define DUTY_ZERO_init 4000     // 1 divided by 0,00025 seconds --> 4000 Hz
#define DUTY_ZERO 0
#define DUTY_AV 0.8
#define DUTY_AR -0.8

//Autres variables
#define seuil_B 240
#define seuil_H 1500

void initialisation (void);

void declamp_AR (void);//fonction pour declamper les pattes ar
void clamp_AR (void);//fonction pour clamper les pattes ar


#endif
