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

	
	sys_tick_init();	//ϵͳ��ʱ����ʼ��
	pwm_tim3_init();	//TIM3 pwm����ʼ��
	pwm_tim1_init();	//TIM1 pwm����ʼ��
	usart_init();			//����һ ����ͨ�ų�ʼ��
	led_init(LED1);		//led1��ʼ��
	RGB_init();
	kqm_init();				//kqm��ʼ��
	su_o3t_init();		//su_o3t��ʼ��
	buzzer_init();		//��������ʼ��
	dth11_init();			//dth11��ʼ��
//	AD_light_init();				//ADģ��ת����ʼ�� 
//	AD_smoke_init();	//
	ADC1_DMA_init();	//ADC1��ͨ��+DMAת�˳�ʼ��
	rtc_init();
	usart_send_string("Ҧ����\r\n");
	while(1){
		su_time_scale(15);		//��������
		kqm_time_scale(18);		//kqm������
		dht_time_scale(500);	//dht������
		ADC_time_scale(12);		//ADC1 2 DMA
		
	}
}

//������ʾʱ��
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










