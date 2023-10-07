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


int main(){
	sys_tick_init();	//ϵͳ��ʱ����ʼ��
	usart_init();			//����һ ����ͨ�ų�ʼ��

	led_init(LED1);		//led1��ʼ��
	led_init(LED2);		//led1��ʼ��
	key_init();
	freertos_demo();

} 



void vApplicationStackOverflowHook(void)
{
	while(1)
	{
		
	}
}








