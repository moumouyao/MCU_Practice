#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"                  // Device header
//LEDµ∆∫Í∂®“Â
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4

void led_init(uint32_t t);
void led_enable(uint32_t t);
void led_disable(uint32_t t);
#endif
