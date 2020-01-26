/*
 * adc.c
 *
 *  Created on: 10.01.2020
 *      Author: Damian
 */


#include <avr/io.h>
#include "adc.h"

void adc_init(void){
	ADMUX |= (1<<REFS0)|(1<<REFS1);
	ADCSRA |= (1<<ADEN);
}

uint16_t adc_measure(uint8_t mux){
	ADMUX |= (ADMUX & 0xF8) | mux;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));

	return ADCW;
}

uint32_t sr(uint8_t mux){
	static uint32_t sr = 0;
	uint16_t temp = 0;

	temp = adc_measure(mux);

	sr = KFIL * sr;
	sr=sr+temp;
	sr=sr/(KFIL+1);

	return sr;
}

uint16_t temp_measure(uint16_t temp){

	float v = 0;
	float temper = 0;

	v = temp * 0.0025;
	temper = v / 0.002;
	temper += 25;

	return temper;
}
