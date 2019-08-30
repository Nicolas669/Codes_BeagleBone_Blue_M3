/*
 *  main.c
 */

#include <stdio.h>

#include "motor.h"
#include "gpio.h"
#include "deplacement.h"
#include "adc.h"
#include "pwm.h"


int main (int argc, char ** argv)
{
	printf("debut du programme\n\n");
	int position;
	float positionmm;
	int nbpas=1,etat=1;
	
	initialisation();

	//clamp_AR();

	declamp_AR();
	//clamp_AR(); 

	return 0;
}
