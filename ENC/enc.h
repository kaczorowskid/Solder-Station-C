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
#define ENC_TYPE 1			//typ enkodera: 0-pe�nokrokowy, 1-p�krokowy, 2-czterokrokowy

#define PORT_DIR	DDRD			//port dla enkodera
#define PORT_OUT	PORTD			//port dla enkodera
#define PORT_IN		PIND			//port dla enkodera


#define PIN_ENC 0b00011000		//piny pod kt�re pod��czony jest enkoder
//warto�ci dla poszczeg�lnych stan�w enkodera
//w zale�no�ci od u�ytych pin�w
#define STAN1 0b00001000
#define STAN2 0b00010000
#define STAN3 0b00011000

//*********************************************************************************
#define ENC_IN (PORT_IN & PIN_ENC)

void encoder_port(void);	//ustawienie wej�� enkodera
void encoder_reset(void);	//wywo�a� przed ka�dym nowym u�yciem enkodera
void encoder(void);		//cyklicznie wywo�ywa� w przerwaniach, czym wi�ksza cz�stotliwo�� tym lepiej
int8_t enc_get(void);		//dodawa� jako sk�adnik modyfikowanej zmiennej, np. odczyt += enc_get();
//*********************************************************************************



#endif /* ENC_ENC_H_ */
