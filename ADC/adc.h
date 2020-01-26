/*
 * adc.h
 *
 *  Created on: 10.01.2020
 *      Author: Damian
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#define KFIL 150

void adc_init(void);
uint16_t adc_measure(uint8_t mux);
uint16_t temp_measure(uint16_t temp);
uint32_t sr(uint8_t mux);

#endif /* ADC_ADC_H_ */
