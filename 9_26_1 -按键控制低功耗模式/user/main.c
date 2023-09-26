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
	usart_init();			//����һ ����ͨ�ų�ʼ��
	led_init(LED1);		//led1��ʼ��
	RGB_init();
	su_o3t_init();		//su_o3t��ʼ��
	buzzer_init();		//��������ʼ��
	rtc_init();
	key_init();
	key1_interrupt_init();
	usart_send_string("Ҧ����\r\n");
	if(BKP_ReadBackupRegister(BKP_DR2) == 0x01){
		printf("�˳�����ģʽ\r\n");
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
			//ʹ�� RTC �ͺ󱸼Ĵ�������
			PWR_BackupAccessCmd(ENABLE);
			BKP_WriteBackupRegister(BKP_DR2, 0);
			PWR_BackupAccessCmd(DISABLE);
	}
	while(1){
		current_time_scale(1000);
		lowpor_time_scale(20);
		
	}
}











