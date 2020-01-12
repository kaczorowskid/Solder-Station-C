/*
 * menu.c
 *
 *  Created on: 08.01.2020
 *      Author: Damian
 */


#include <avr/io.h>
#include <util/delay.h>
#include "menu.h"

uint8_t menu_pos;

pid_ust_t pid_ust;

const menu_t menu[] = {
		{"> Ustawienie PID  ", "Informacje      ", 0 },
		{"Ustawienia PID  ", "> Informacje    ", 0},
		{"> Wyjscie       ", "                ", 0}
};

const menu_t submenu[] ={
		{" KP  KI  KD  KT ", 0, settings_func },
		{"Jan Kowalski    ", "Warszawa 2020   ", exit_info},
		{0, 0, exit}
};


void menu_change(uint8_t pos){

	uint8_t *first_line_pointner = (pos < 10) ? menu[pos - 1].first_line : submenu[pos - 12].first_line;
	uint8_t *second_line_pointner = (pos < 10) ? menu[pos - 1].second_line : submenu[pos - 12].second_line;


	lcd_locate(0,0);
	lcd_str(first_line_pointner);
	lcd_locate(1,0);
	lcd_str(second_line_pointner);

	if(pos > 10 && submenu[pos - 12].callback) submenu[pos - 12].callback();
}

void start_display(uint16_t current_temp, uint16_t temp, uint8_t blink_flag, uint8_t pwm){
	lcd_locate(0,0);
	lcd_big_int(current_temp);
	lcd_blink_int(temp, 0, 12, blink_flag, 15);
}

void clear(void){
	lcd_locate(1,0);
	lcd_str(" ");
	lcd_locate(1,3);
	lcd_str("  ");
	lcd_locate(1,7);
	lcd_str("  ");
	lcd_locate(1,11);
	lcd_str("  ");
}

void settings_func(void){
	static uint8_t pos = 0;
	uint8_t blink_tab[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

	clear();
	read_kbc(&pos, 0, 0);

	if(pos > 3) {
		pos = 0;
		menu_pos = 1;
	}
	if(pid_ust.KP < 10){
		lcd_locate(1,2);
		lcd_char(' ');
	}
	lcd_blink_int(pid_ust.KP, 1, 1, blink_tab[0][pos], 15);

	if(pid_ust.KI < 10){
		lcd_locate(1,6);
		lcd_char(' ');
	}
	lcd_blink_int(pid_ust.KI, 1, 5, blink_tab[1][pos], 15);
	lcd_blink_int(pid_ust.KD, 1, 9, blink_tab[2][pos], 15);
	lcd_blink_int(pid_ust.KT, 1, 13, blink_tab[3][pos], 15);

	encoder();

	if(pos == 0) pid_ust.KP += enc_get();
	if(pos == 1) pid_ust.KI += enc_get();
	if(pos == 2) pid_ust.KD += enc_get();
	if(pos == 3) pid_ust.KT += enc_get();
}

void exit(void){
	menu_pos = 0;
}

void exit_info(void){
	static uint8_t pos = 0;
	read_kbc(&pos, 0);

	if(pos > 0) menu_pos = 2;
}
