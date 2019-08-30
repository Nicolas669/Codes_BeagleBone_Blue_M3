/*
 *  adc.h
 */

#ifndef _ADC_H
#define _ADC_H

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define unlikely(x)	__builtin_expect (!!(x), 0)

//#define CHANNELS 8
#define IIO_DIR "/sys/bus/iio/devices/iio:device0"
#define RAW_MAX 4095
#define RAW_MIN 0
#define MAX_BUF 64

/*
#define ADC_WIDTH 1800
#define ADC_HALF_WIDTH 900
#define ADC_BIAIS 0
*/

int adc_init(void); 
//initializes the analog to digital converter for reading

int adc_cleanup(void); 
//cleans up the ADC subsystem. Call before program closes down

int adc_read_raw(int ch); 
//reads the raw integer ADC value for a particular channel (ch channel 0-7)

double adc_read_volt(int ch); 
//reads an adc voltage.


#endif
