#ifndef __KQM_H_
#define __KQM_H_

#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "string.h"

extern uint8_t usart_kqm_RXpacket[8];

void kqm_init(void);
uint8_t usart_get_kqm__RXflag(void);
void air_analysis(void);

#endif
