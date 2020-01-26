/*
 * main.c
 *
 *  Created on: 04.01.2020
 *      Author: Damian
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCD/lcd44780.h"
#include "ENC/enc.h"
#include "KEY/key.h"
#include "MENU/menu.h"
#include "ADC/adc.h"
#include "PID/pid.h"


volatile uint8_t timer, timer1;
extern uint8_t menu_pos;
uint8_t temp_change_flag;
int16_t temp = 150;
uint8_t pwm = 0;
uint16_t pwm1;
uint8_t current_temp;

pid_ust_t pid_ust;
pid_t pid_s;

void temp_change(void);
void pid_change(void);
void start_pid(void);

int main(void) {
	lcd_init();

	encoder_port();
	encoder_reset();

	pid_ust.KD = 2;
	pid_ust.KI = 2;
	pid_ust.KP = 2;
	pid_ust.KT = 5;

//	pid_s.KD = 2;
//	pid_s.KI = 2;
//	pid_s.KP = 2;
//	pid_s.KT = 10;

	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK |= (1 << OCIE1A);
	OCR1A = 200;

	TCCR2 |= (1 << WGM21) | (1 << CS20);
	OCR2 = 100;
	TIMSK |= (1 << OCIE2);

	DDRC |= (1 << PC5);
	PORTC &= ~(1 << PC5);



	adc_init();
	init_kbc();
	lcd_cls();

	sei();

	while (1) {
		encoder();

		start_pid();

		if (menu_pos > 3 && menu_pos < 10)
			menu_pos = 3;

		if (temp_change_flag == 1 && !menu_pos)
			temp += enc_get();
		else if (!menu_pos || menu_pos == 12 || menu_pos == 13)
			encoder_reset();
		else
			menu_pos += enc_get();

		if (!menu_pos) {
			if(!timer1){
				start_display(current_temp, temp, temp_change_flag, pwm);
				timer1 = 15;
			}
//			start_display(current_temp, temp, temp_change_flag, pwm);
			read_kbc(0, &menu_pos, 0);
		} else if (menu_pos != 12)
			read_kbc(&menu_pos, 0, 1);
		else if (menu_pos == 12)
			read_kbc(0, 0, 0);

		menu_change(menu_pos);
		temp_change();
	}
}

void temp_change(void) {
	if (!menu_pos)
		read_key(&temp_change_flag);
	if (temp_change_flag > 1)
		temp_change_flag = 0;

	if (temp < 0)
		temp = 0;
	if (temp > 500)
		temp = 500;

}

void pid_change(void) {
	pid_s.KD = pid_ust.KD;
	pid_s.KI = pid_ust.KI;
	pid_s.KP = pid_ust.KP;
	pid_s.KT = pid_ust.KT;
}

void start_pid(void) {
	current_temp = temp_measure(sr(3));
	pwm1 = pid(temp, current_temp, &pid_s);

	pwm = pwm1 / 2.5;
	if (pwm > 100)
		pwm = 100;

	pid_change();
}

ISR(TIMER1_COMPA_vect) {
	uint8_t x;
	x = timer;
	if (x)
		timer = --x;

	x = timer1;
	if (x)
		timer1 = --x;

}

ISR(TIMER2_COMP_vect) {
	static uint8_t cnt;

	if (cnt >= pwm1)
		PORTC |= (1 << PC5);
	else
		PORTC &= ~(1 << PC5);

	cnt++;
}
