/*
 * enc.h
 *
 *  Created on: 30.12.2019
 *      Author: Damian
 */

#ifndef ENC_ENC_H_
#define ENC_ENC_H_

//*********************************************************************************
//--- USTAWIENIA ---
//
#define ENC_TYPE 1			//typ enkodera: 0-pe³nokrokowy, 1-pó³krokowy, 2-czterokrokowy

#define PORT_DIR	DDRD			//port dla enkodera
#define PORT_OUT	PORTD			//port dla enkodera
#define PORT_IN		PIND			//port dla enkodera


#define PIN_ENC 0b00011000		//piny pod które pod³¹czony jest enkoder
//wartoœci dla poszczególnych stanów enkodera
//w zale¿noœci od u¿ytych pinów
#define STAN1 0b00001000
#define STAN2 0b00010000
#define STAN3 0b00011000

//*********************************************************************************
#define ENC_IN (PORT_IN & PIN_ENC)

void encoder_port(void);	//ustawienie wejœæ enkodera
void encoder_reset(void);	//wywo³aæ przed ka¿dym nowym u¿yciem enkodera
void encoder(void);		//cyklicznie wywo³ywaæ w przerwaniach, czym wiêksza czêstotliwoœæ tym lepiej
int8_t enc_get(void);		//dodawaæ jako sk³adnik modyfikowanej zmiennej, np. odczyt += enc_get();
//*********************************************************************************



#endif /* ENC_ENC_H_ */
