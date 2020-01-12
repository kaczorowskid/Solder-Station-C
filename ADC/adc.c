/*
 * adc.c
 *
 *  Created on: 10.01.2020
 *      Author: Damian
 */


#include <avr/io.h>
#include "adc.h"

void adc_init(void){
	ADMUX |= (1<<REFS1)|(1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}

uint16_t adc_measure(uint8_t mux){
	ADMUX |= (ADMUX & 0xF8) | mux;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));

	return ADCW;
}

uint16_t temp_measure(uint16_t temp){
	static uint32_t result;



	return result;
}
