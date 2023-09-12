#ifndef __EXTI_H_
#define __EXTI_H_

#include "stm32f10x.h"                  // Device header
//°´¼üÖµ
enum key{KEY1 = 1, KEY2, KEY3, KEY4};
void key1_exit_init(void);
uint8_t get_key_val(uint8_t key);
void key2_exit_init(void);
void key4_exit_init(void);
void key3_exit_init(void);
#endif
