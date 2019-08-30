/*
 *  motor.c
 */

#include "motor.h"

// polarity of the motor connections
static const double polarity[]={1.0,-1.0,-1.0,1.0};

static int init_flag = 0;
static int stby_state = 0;
static int dirA_chip[CHANNELS];
static int dirA_pin[CHANNELS];
static int dirB_chip[CHANNELS];
static int dirB_pin[CHANNELS];
static int pwmss[CHANNELS];
static int pwmch[CHANNELS];


int motor_init_freq(int pwm_frequency_hz)
{
	int i;

	// motor 3
	dirA_chip[2]=MDIR3A_CHIP;
	dirA_pin[2]=MDIR3A_PIN;
	dirB_chip[2]=MDIR3B_CHIP;
	dirB_pin[2]=MDIR3B_PIN;
	pwmss[2]=2;
	pwmch[2]='A';

	// set up pwm channels
	if(unlikely(pwm_init(1,pwm_frequency_hz))){
		fprintf(stderr,
"ERROR in motor_init, failed to initialize pwm subsystem 1\n");
		return -1;
	}
	if(unlikely(pwm_init(2,pwm_frequency_hz))){
		fprintf(stderr,
"ERROR in motor_init, failed to initialize pwm subsystem 2\n");
		return -1;
	}

	// set up gpio pins
	if(unlikely(gpio_init(MOT_STBY, GPIOHANDLE_REQUEST_OUTPUT))){
		fprintf(stderr,
"ERROR in motor_init, failed to set up gpio %d,%d\n", MOT_STBY);
		return -1;
	}
	
	
	if(unlikely(gpio_init(
dirA_chip[2],dirA_pin[2], GPIOHANDLE_REQUEST_OUTPUT))){
		fprintf(stderr,
"ERROR in motor_init, failed to set up gpio %d,%d\n", 
dirA_chip[2],dirA_pin[2]);
		return -1;
	}
	if(unlikely(gpio_init(
dirB_chip[2],dirB_pin[2], GPIOHANDLE_REQUEST_OUTPUT))){
		fprintf(stderr,
"ERROR in motor_init, failed to set up gpio %d,%d\n",
dirB_chip[2],dirB_pin[2]);
		return -1;
	}
	

	// now set all the gpio pins and pwm to something predictable
	stby_state = 0;
	init_flag = 1;
	if(unlikely(motor_free_spin(3))){
		fprintf(stderr,"ERROR in motor_init\n");
		init_flag = 0;
		return -1;
	}
	stby_state = 0;
	init_flag = 1;
	return 0;
}


int motor_free_spin(int motor)
{
	int i;

	// sanity checks
	if(unlikely(motor<0 || motor>CHANNELS)){
		fprintf(stderr,
"ERROR in motor_free_spin, motor argument must be between 0 & %d\n",
 CHANNELS);
		return -1;
	}
	if(unlikely(init_flag==0)){
		fprintf(stderr,
"ERROR in motor_free_spin, call rc_motor_init first\n");
		return -1;
	}

	// case for all channels
	if(motor==3){
		if(motor_free_spin(3)==-1) {return -1;
		}
		return 0;
	}

	// set gpio and pwm for that motor
	if(unlikely(gpio_set_value(
dirA_chip[motor-1],dirA_pin[motor-1], 0))){fprintf(stderr,
"ERROR in motor_free_spin, failed to write to gpio pin %d,%d\n",
dirA_chip[motor-1],dirA_pin[motor-1]);
		return -1;
	}
	if(unlikely(gpio_set_value(
dirB_chip[motor-1],dirB_pin[motor-1], 0))){fprintf(stderr,
"ERROR in motor_free_spin, failed to write to gpio pin %d,%d\n",
dirB_chip[motor-1],dirB_pin[motor-1]);
		return -1;
	}
	if(unlikely(pwm_set_duty(
pwmss[motor-1], pwmch[motor-1], 0.0))){fprintf(stderr,
"ERROR in motor_free_spin, failed to write to pwm %d%c\n",
pwmss[motor-1], pwmch[motor-1]);
		return -1;
	}
	return 0;
}

int motor_set(int motor, double duty)
{
	int a,b,i;

	// sanity checks
	if(unlikely(motor<0 || motor>CHANNELS)){
		fprintf(stderr,
"ERROR in motor_set, motor argument must be between 0 & %d\n", CHANNELS);
		return -1;
	}
	if(unlikely(init_flag==0)){
		fprintf(stderr,
"ERROR in motor_set, call motor_init first\n");
		return -1;
	}

	// check that the duty cycle is within +-1
	if	(duty > 1.0)	duty = 1.0;
	else if	(duty <-1.0)	duty =-1.0;

	if(motor==0){
		for(i=1;i<CHANNELS;i++){
			if(motor_set(i,duty)==-1) return -1;
		}
		return 0;
	}

	// determine the direction pins to H-bridge
	duty=duty*polarity[motor-1];
	if(duty>=0.0){	a=1; b=0;}
	else{		a=0; b=1; duty=-duty;}

	// set gpio and pwm for that motor
	if(unlikely(gpio_set_value(
dirA_chip[motor-1],dirA_pin[motor-1], a))){fprintf(stderr,
"ERROR in motor_set, failed to write to gpio pin %d,%d\n",
dirA_chip[motor-1],dirA_pin[motor-1]);
		return -1;
	}
	if(unlikely(gpio_set_value(
dirB_chip[motor-1],dirB_pin[motor-1], b))){fprintf(stderr,
"ERROR in motor_set, failed to write to gpio pin %d,%d\n",
dirB_chip[motor-1],dirB_pin[motor-1]);
		return -1;
	}
	if(unlikely(pwm_set_duty(
pwmss[motor-1], pwmch[motor-1], duty))){fprintf(stderr,
"ERROR in motor_set, failed to write to pwm %d%c\n",
pwmss[motor-1], pwmch[motor-1]);
		return -1;
	}
	return 0;
}

