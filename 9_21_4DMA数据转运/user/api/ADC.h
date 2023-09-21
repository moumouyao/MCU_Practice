#ifndef __ADC_H_
#define __ADC_H_

#include "stm32f10x.h"                  // Device header

uint16_t AD_get_val(void);
void AD_init(void);

#endif
