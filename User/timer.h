#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x_conf.h"

extern int flag_1HZ;
extern int flag_100HZ;

void timer3_init(uint16_t Handler_Frequency);
void msdelay(int ms);
void walk(void);
void dance(void);
void round_left(void);
void round_right(void);
#endif

