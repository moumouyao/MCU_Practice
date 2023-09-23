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

void light2rgb(void);

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
//	AD_light_init();				//ADģ��ת����ʼ�� 
//	AD_smoke_init();	//
	ADC1_DMA_init();	//ADC1��ͨ��+DMAת�˳�ʼ��
	
	usart_send_string("Ҧ����\r\n");
	while(1){
//		light2rgb();
//		printf("�������� %d\r\n", AD_smoke_Median_filter());
//		printf("CPU�¶� = %f\r\n", AD_temp_Median_filter());
		ADC1_DMA_get_val();
		printf("%d\r\n", ADC1_val[0]);
		printf("%d\r\n", ADC1_val[1]);
		printf("%d\r\n", ADC1_val[2]);
		Delay_s(2);
}

}

/**
  * @brief  ���ݹ���ǿ�ȿ���RGB��
  * @param  None
  * @retval None
  */
void light2rgb(void){
	float val = (((float)AD_light_Median_filter() / 4095) * 100);
	TIM_SetCompare1(TIM3, val);
}












