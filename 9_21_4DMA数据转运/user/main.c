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
	
	sys_tick_init();	//ϵͳ��ʱ����ʼ��
	pwm_tim3_init();	//TIM3 pwm����ʼ��
	pwm_tim1_init();	//TIM1 pwm����ʼ��
	usart_init();			//����һ ����ͨ�ų�ʼ��
	led_init(LED1);		//led1��ʼ��
	kqm_init();				//kqm��ʼ��
	su_o3t_init();		//su_o3t��ʼ��
	buzzer_init();		//��������ʼ��
	dth11_init();			//dth11��ʼ��
	AD_init();				//ADģ��ת����ʼ�� 
	
	usart_send_string("Ҧ����");
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












