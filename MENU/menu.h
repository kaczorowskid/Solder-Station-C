/*
 * menu.h
 *
 *  Created on: 08.01.2020
 *      Author: Damian
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

typedef struct {
	const char *first_line;
	const char *second_line;
	void (*callback)(void);
}menu_t;

void menu_change(uint8_t pos);
void start_display(uint16_t current_temp, uint16_t temp, uint8_t pwm);

void test(void);

#endif /* MENU_MENU_H_ */
