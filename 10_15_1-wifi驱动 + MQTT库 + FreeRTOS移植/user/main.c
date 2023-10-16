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
#include "bsp_lcd.h"
#include "my_lcd.h"
#include "myrtos.h"
#include "my_spi_flash.h"

void api_init(void);

int main(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	api_init();
	
	freertos_demo();
	while(1){
			printf("\r\nFreeRTOS�Ѿ�����\r\n");
	}
} 



void vApplicationStackOverflowHook(void)
{
	while(1)
	{
		printf("\r\n����ջ���\r\n");
	}
}

void api_init(void){
	usart_init();			//����һ ����ͨ�ų�ʼ��
	led_init(LED1);		//led1��ʼ��
	led_init(LED2);		//led1��ʼ��
	key_init();				//������ʼ��
	buzzer_init();		//��������ʼ��
	usart_send_string(USART1, "Ҧ����\r\n");
	dth11_init();			//dth11��ʼ��
	LCD_Init();				//LCD����ʼ��
	kqm_init();				//kqm��ʼ��
	su_o3t_init();		//su_o3t��ʼ��
	dth11_init();			//dth11��ʼ��
	ADC1_DMA_init();	//ADC1��ͨ��+DMAת�˳�ʼ��
	sFLASH_Init();
	esp8266_init();
	show_index2LCD();
	Delay_ms(3000);
	wifi_init();
	subscription_service();
	rtc_init();
}






