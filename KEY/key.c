/*
 * key.c
 *
 *  Created on: 08.01.2020
 *      Author: Damian
 */

#include <avr/io.h>
#include "key.h"
#include "../LCD/lcd44780.h"

uint32_t cnt = 0;
uint8_t flag = 0;

void init_kbc(void) {
	KEY_DIR &= ~KEY;
	KEY_PORT |= KEY;
}

void reset_cnt(void){
	cnt = 0;
	if (KEY_NO_PRESS) cnt = 0;
}

void read_kbc(uint8_t *short_press, uint8_t *long_press, uint8_t big_incr) {
	if (KEY_PRESS) {
		cnt++;
		if(cnt > MAX_CNT) flag = 1;
		else flag = 0;
	}
	if (KEY_NO_PRESS) flag = 1;


//	lcd_locate(0,12);
//	lcd_int(cnt);
//	lcd_locate(1,12);
//	lcd_int(flag);



	if (flag) {
		if (cnt > MAX_CNT && cnt > MIN_CNT) {
			(*long_press) = 1;
			reset_cnt();
		}

		else if (cnt > MIN_CNT && cnt < MAX_CNT) {
			(*short_press)++;
			if(big_incr){
				if(KEY_PRESS && (*short_press) == 1 || (*short_press) == 2 || (*short_press) == 3) (*short_press) += 10;
			}

			reset_cnt();
		}
	}

}

