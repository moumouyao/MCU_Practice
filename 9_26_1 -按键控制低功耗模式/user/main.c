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
void show_time(void);
void key_control(void);


int main(){
	sys_tick_init();
	usart_init();			//串口一 串口通信初始化
	led_init(LED1);		//led1初始化
	RGB_init();
	su_o3t_init();		//su_o3t初始化
	buzzer_init();		//蜂鸣器初始化
	rtc_init();
	key_init();
	key1_interrupt_init();
	usart_send_string("姚乐毅\r\n");
	if(BKP_ReadBackupRegister(BKP_DR2) == 0x01){
		printf("退出待机模式\r\n");
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
			//使能 RTC 和后备寄存器访问
			PWR_BackupAccessCmd(ENABLE);
			BKP_WriteBackupRegister(BKP_DR2, 0);
			PWR_BackupAccessCmd(DISABLE);
	}
	while(1){
		current_time_scale(1000);
		lowpor_time_scale(20);
		
	}
}











