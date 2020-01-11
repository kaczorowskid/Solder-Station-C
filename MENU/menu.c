/*
 * menu.c
 *
 *  Created on: 08.01.2020
 *      Author: Damian
 */


#include <avr/io.h>
#include <util/delay.h>
#include "menu.h"
//#include "../LCD/lcd44780.h"

//extern volatile uint8_t tim1;

const menu_t menu[] = {
		{"> Ustawie", "Informacje      ", 0 },
		{"Ustawienia PID  ", "> Informacje    ", 0},
		{"> Wyjscie       ", "                ", 0}
};

const menu_t submenu[] ={
		{" KP  KI  KD  KT ", 0, test }, //" 08  22  10  02 "
		{"Jan Kowalski    ", "Warszawa 2020   ", 0},
};


void menu_change(uint8_t pos){

	uint8_t *first_line_pointner = (pos < 10) ? menu[pos - 1].first_line : submenu[pos - 12].first_line;
	uint8_t *second_line_pointner = (pos < 10) ? menu[pos - 1].second_line : submenu[pos - 12].second_line;


	lcd_locate(0,0);
	lcd_str(first_line_pointner);
	lcd_locate(1,0);
	lcd_str(second_line_pointner);

	if(pos > 10 && submenu[pos].callback) submenu[pos - 12].callback();
}

void start_display(uint16_t current_temp, uint16_t temp, uint8_t pwm){
	lcd_locate(0,0);
	lcd_big_int(current_temp);
//	lcd_blink_int(temp, 0, 13, 1, 15);
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

void test(void){
	static uint8_t pos = 0;
	uint8_t blink_tab[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

	clear();
	read_kbc(&pos, 0, 0);
	if(pos > 3) pos = 0;
	lcd_blink_int(pos, 1, 1, blink_tab[0][pos], 15);
	lcd_blink_int(12, 1, 5, blink_tab[1][pos], 15);
	lcd_blink_int(21, 1, 9, blink_tab[2][pos], 15);
	lcd_blink_int(17, 1, 13, blink_tab[3][pos], 15);
}
