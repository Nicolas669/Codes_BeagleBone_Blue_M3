/*
 *  deplacement.c
 */

#include "deplacement.h"

void initialisation (void)
{

	printf("initialisation M3\n");
	
	gpio_init(GPIO_M3_chip, GPIO_M3_pin, GPIOHANDLE_REQUEST_OUTPUT);
	gpio_set_value(GPIO_M3_chip, GPIO_M3_pin, 0);

	motor_init_freq(DUTY_ZERO_init);
	sleep(1);
	printf("Fin initialisaton\n\n");
}

void clamp_AR (void)
{
	printf("\nFonction clampe AR\n");
	double courant_M3 =0;
	int i =0;
	sleep(1);

	//on enable le moteur
	gpio_set_value(GPIO_M3_chip, GPIO_M3_pin, 1); // 1 --> enable

	//on alimente le moteur
	courant_M3 = adc_read_volt(adc_M3);
	while(courant_M3 <= 1200)
	{

		for( i=0;i<=6;i++)
//Ceci est un boucle afin de temporiser le temps de convertion
		{
			courant_M3 = adc_read_volt(adc_M3);
			usleep(3000);
		}
		sleep(1);
		courant_M3 = adc_read_volt(adc_M3);  
		motor_set(3,DUTY_AV);                            
		printf("Voici le courant : %d\n",courant_M3);
	}
	//on eteint le moteur
	motor_set(3,DUTY_ZERO);

	//On disable le moteur:
	gpio_set_value(GPIO_M3_chip, GPIO_M3_pin, 0);

	sleep(1);
	printf("Fin clamp AR\n\n");
}


void declamp_AR (void)
{
	printf("\nFonction declampe AR\n");
	double courant_M3 =0;
	int i =0;
	sleep(1);

	//on enable le moteur
	gpio_set_value(GPIO_M3_chip, GPIO_M3_pin, 1); // 1 --> enable

	courant_M3 = adc_read_volt(adc_M3);
	sleep(1);
	
	//on alimente le moteur
	while(courant_M3 >= seuil_B)
	{

		usleep(3000);

    		for( i=0;i<=6;i++) 
//Ceci est un boucle afin de temporiser le temps de convertion
		{
			courant_M3 = adc_read_volt(adc_M3);
			usleep(3000);
		}
		sleep(1);
		motor_set(3,DUTY_AR);
		courant_M3 = adc_read_volt(adc_M3);
		printf("Voici le courant : %d\n",courant_M3);
	}
	//on eteint le moteur
	motor_set(3,DUTY_ZERO);
	sleep(1);

	//On disable le moteur:
	gpio_set_value(GPIO_M3_chip, GPIO_M3_pin, 0);

	printf("Fin declamp AR\n");
}

	
