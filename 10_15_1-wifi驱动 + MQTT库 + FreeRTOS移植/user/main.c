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
			printf("\r\nFreeRTOS已经崩溃\r\n");
	}
} 



void vApplicationStackOverflowHook(void)
{
	while(1)
	{
		printf("\r\n任务栈溢出\r\n");
	}
}

void api_init(void){
	usart_init();			//串口一 串口通信初始化
	led_init(LED1);		//led1初始化
	led_init(LED2);		//led1初始化
	key_init();				//按键初始化
	buzzer_init();		//蜂鸣器初始化
	usart_send_string(USART1, "姚乐毅\r\n");
	dth11_init();			//dth11初始化
	LCD_Init();				//LCD屏初始化
	kqm_init();				//kqm初始化
	su_o3t_init();		//su_o3t初始化
	dth11_init();			//dth11初始化
	ADC1_DMA_init();	//ADC1多通道+DMA转运初始化
	sFLASH_Init();
	esp8266_init();
	show_index2LCD();
	Delay_ms(3000);
	wifi_init();
	subscription_service();
	rtc_init();
}






