/*
 * enc.c
 *
 *  Created on: 30.12.2019
 *      Author: Damian
 */


#include <avr/io.h>
#include "enc.h"
volatile int8_t encoder_step=0, encoder_last;

//*******************************************************************************

void encoder (void) // 00 01 11 10 00 01 11 10
{
#if ENC_TYPE!=2
  static int8_t encoder_dir=0;
#endif
  static int8_t encoder_state;
  encoder_state=ENC_IN;
  if (encoder_state != encoder_last)
    {
      switch(encoder_last) //pozycja poprzednia
      {
	case 0:
#if ENC_TYPE==2
	  if (encoder_state==STAN1) encoder_step++;
	  if (encoder_state==STAN2) encoder_step--;
#else
	  if (encoder_state==STAN1) encoder_dir=1; else encoder_dir=-1;
#endif
	  break;

	case STAN3:
#if ENC_TYPE==2
	  if (encoder_state==STAN1) encoder_step--;
	  if (encoder_state==STAN2) encoder_step++;
#else
	  if (encoder_state==STAN2) encoder_dir=1; else encoder_dir=-1;
#endif
	  break;

	case STAN1:
#if ENC_TYPE==2
	  if (encoder_state==0) encoder_step--;
	  if (encoder_state==STAN3) encoder_step++;
#else
	  if (encoder_state==STAN3 && encoder_dir>0) encoder_step--;
	  if (encoder_state==0 && encoder_dir<0) encoder_step++;
#endif
	break;

#if ENC_TYPE==2
	case STAN2:
	  if (encoder_state==STAN3) encoder_step--;
	  if (encoder_state==0) encoder_step++;
	break;
#endif

#if ENC_TYPE==1
	case STAN2:
	  if (encoder_state==STAN3 && encoder_dir<0) encoder_step++;
	  if (encoder_state==0 && encoder_dir>0) encoder_step--;
	break;
#endif


      }
      encoder_last = encoder_state;
    }
}

//*******************************************************************************

int8_t enc_get(void)		//przyrost impulsów
{
  int8_t ret_encoder_step=encoder_step;
  encoder_step=0;
  return ret_encoder_step;
}

//*******************************************************************************

void encoder_reset(void)	//reset enkodera przed nowym u¿yciem
{
  encoder_step=0;
  encoder_last=ENC_IN;
}

//*******************************************************************************
void encoder_port(void)		//ustawienie wejœæ enkodera
{
  PORT_DIR &= ~PIN_ENC;
  PORT_OUT |= PIN_ENC;
}

//*******************************************************************************
