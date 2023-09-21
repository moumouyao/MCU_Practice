#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "interrupt.h"
#include "timer.h"
#include "usart.h"
#include <string.h>
#include "kqm.h"
#include "su_03t.h"
#include "dht11.h"
#include "ADC.h"
#include "pwm.h"
#include "MyDMA.h"

uint8_t data1[] = {0x01, 0x02, 0x03, 0x04};
uint8_t data2[4] = {0};

int main(){
	
	sys_tick_init();	//系统定时器初始化
	pwm_tim3_init();	//TIM3 pwm波初始化
	pwm_tim1_init();	//TIM1 pwm波初始化
	usart_init();			//串口一 串口通信初始化
	led_init(LED1);		//led1初始化
	kqm_init();				//kqm初始化
	su_o3t_init();		//su_o3t初始化
	buzzer_init();		//蜂鸣器初始化
	dth11_init();			//dth11初始化
	AD_init();				//AD模数转换初始化 
	
	usart_send_string("姚乐毅");
	MyDMA_init((uint32_t)data1, (uint32_t)data2, 4);
	usart_send_array(data1, 4);
	usart_send_array(data2, 4);
	while(1){
		data1[0]++;data1[2]++;data1[2]++;data1[3]++;
		MyDMA_Transfer();
		usart_send_array(data1, 4);
		usart_send_array(data2, 4);
		Delay_s(2);
}

}












