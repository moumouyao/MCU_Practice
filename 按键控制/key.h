#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f10x.h"                  // Device header

void key_init(void);
uint8_t key_get_num(void);
#endif
