/*
 * key.h
 *
 *  Created on: 08.01.2020
 *      Author: Damian
 */

#ifndef KEY_KEY_H_
#define KEY_KEY_H_

#define KEY_DIR DDRD
#define KEY_PORT PORTD
#define KEY_PIN PIND

#define KEY (1<<PD2)

#define KEY_PRESS (!(KEY_PIN & KEY))
#define KEY_NO_PRESS (KEY_PIN & KEY)

#define MAX_CNT 500
#define MIN_CNT 100


void init_kbc(void);
void read_kbc(uint8_t *short_press, uint8_t *long_press, uint8_t big_incr);
void reset_cnt(void);
void read_key(uint8_t *short_press);

#endif /* KEY_KEY_H_ */
