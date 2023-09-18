#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "interrupt.h"
#include "timer.h"
#include "usart.h"
#include <string.h>
#include "ic.h"

//void key_led(void);
void key_led(void);
void water_led(void);

int main(){
	sys_tick_init();
	usart_init();
	ic_init();
	time3_init();
	pwm_set_compare1(50);						//Duty = CCR / 100
	pwm_set_prescaler(7200 - 1);			//Freg = 72M / (PSC + 1) / 100
	while(1){
		usart_send_string("Y");
		usart_send_num(ic_get_freg(), 8);
		Delay_s(1);
	}
}














