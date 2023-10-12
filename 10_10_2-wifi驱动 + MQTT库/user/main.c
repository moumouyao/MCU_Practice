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
#include "my_spi_flash.h"
#include "esp8266.h"


extern const unsigned char gImage_photos2[86408];

int main(){

	
	sys_tick_init();	//系统定时器初始化
	pwm_tim3_init();	//TIM3 pwm波初始化
	pwm_tim1_init();	//TIM1 pwm波初始化
	usart_init();			//串口一 串口通信初始化
	LCD_Init();				//LCD屏初始化
	LCD_Clear(LIGHTGREEN);
	led_init(LED1);		//led1初始化
	led_init(LED2);
	RGB_init();
	//kqm_init();				//kqm初始化
	su_o3t_init();		//su_o3t初始化
	buzzer_init();		//蜂鸣器初始化
	//dth11_init();			//dth11初始化
	//ADC1_DMA_init();	//ADC1多通道+DMA转运初始化
	
	sFLASH_Init();
	esp8266_init();
	usart_send_string(USART1, "姚乐毅\r\n");
	
	//LCD_ShowPhoto(0,0 ,240 , 320, (uint8_t*)gImage_photos2);
	show_index2LCD();
	
	//usart_send_string(USART3, "AT\r\n");
	Delay_s(3);
	wifi_init();

	subscription_service();
	//rtc_init();
//	if(mqtt2server(property_publish_cstring, property_payload, "success") == 0){
//									printf("\r\n数据发送成功\r\n");
//									
//								}
//								else{
//									printf("\r\n数据发送失败\r\n");
//								}
	while(1){
		su_time_scale(20);		//语音播报
		kqm_time_scale(18);		//kqm传感器
		dht_time_scale(500);	//dht传感器
		ADC_time_scale(12);		//ADC1 2 DMA
		current_time2LCD_scale(5);
		show_data2LCD_scale(5);
		//usart12usart3();
	}
}











