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

typedef struct {
	uint8_t KP;
	uint8_t KI;
	uint8_t KD;
	uint8_t KT;
}pid_ust_t;

extern pid_ust_t pid_ust;

void menu_change(uint8_t pos);
void start_display(uint16_t current_temp, uint16_t temp, uint8_t blink_flag, uint8_t pwm);

void settings_func(void);
void exit(void);
void exit_info(void);

#endif /* MENU_MENU_H_ */
