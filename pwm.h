/*
 * pwm.h
 */

#ifndef RC_PWM_H
#define RC_PWM_H

#include <stdio.h>
#include <stdlib.h> // for atoi
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <glob.h>



#define MIN_HZ 1
#define MAX_HZ 1000000000
#define MAXBUF 128
#define SYS_DIR "/sys/class/pwm"

// ocp only used for exporting right now, 
//everything else through SYS_DIR
// to allow for shorter strings and neater code.
#define OCP_DIR "/sys/devices/platform/ocp/4830%d000.epwmss/4830%d200.pwm/pwm"
#define OCP_OFFSET	66

// preposessor macros
#define unlikely(x)	__builtin_expect (!!(x), 0)


int pwm_init(int ss, int frequency);

int pwm_cleanup(int ss);

int pwm_set_duty(int ss, char ch, double duty);

int pwm_set_duty_ns(int ss, char ch, unsigned int duty_ns);


#endif 
