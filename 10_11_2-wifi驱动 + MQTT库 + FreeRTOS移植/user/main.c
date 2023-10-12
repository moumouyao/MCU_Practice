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


int main(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	sys_tick_init();	//系统定时器初始化
	usart_init();			//串口一 串口通信初始化

	led_init(LED1);		//led1初始化
	led_init(LED2);		//led1初始化
	key_init();				//按键初始化
	buzzer_init();		//蜂鸣器初始化
	usart_send_string(USART1, "姚乐毅\r\n");
	
	
	
//	time6_init();
//	time7_init();

	freertos_demo();

} 



void vApplicationStackOverflowHook(void)
{
	while(1)
	{
		printf("\r\n任务栈溢出\r\n");
	}
}








