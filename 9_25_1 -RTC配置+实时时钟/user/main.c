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
#include "RTC.h"

void light2rgb(void);


int main(){

	
	sys_tick_init();	//系统定时器初始化
	pwm_tim3_init();	//TIM3 pwm波初始化
	pwm_tim1_init();	//TIM1 pwm波初始化
	usart_init();			//串口一 串口通信初始化
	led_init(LED1);		//led1初始化
	RGB_init();
	kqm_init();				//kqm初始化
	su_o3t_init();		//su_o3t初始化
	buzzer_init();		//蜂鸣器初始化
	dth11_init();			//dth11初始化
//	AD_light_init();				//AD模数转换初始化 
//	AD_smoke_init();	//
	ADC1_DMA_init();	//ADC1多通道+DMA转运初始化
	rtc_init();
	usart_send_string("姚乐毅\r\n");
	while(1){
		su_time_scale(15);		//语音播报
		kqm_time_scale(18);		//kqm传感器
		dht_time_scale(500);	//dht传感器
		ADC_time_scale(12);		//ADC1 2 DMA
		
	}
}

//串口显示时间
void show_time(void){
	time_t current_sec = 0;
	current_sec = RTC_GetCounter();
	struct tm *time_info = NULL;
	time_info = localtime(&current_sec);
	printf("%d-%d-%d-%d:%d:%d\r\n", time_info->tm_year + 1900,
																	time_info->tm_mon + 1, 
																	time_info->tm_mday, 
																	time_info->tm_hour, 
																	time_info->tm_min, 
																	time_info->tm_sec);	
}










