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
	
	sys_tick_init();	//系统定时器初始化
	pwm_tim3_init();	//TIM3 pwm波初始化
	pwm_tim1_init();	//TIM1 pwm波初始化
	usart_init();			//串口一 串口通信初始化
	led_init(LED1);		//led1初始化
	kqm_init();				//kqm初始化
	su_o3t_init();		//su_o3t初始化
	buzzer_init();		//蜂鸣器初始化
	dth11_init();			//dth11初始化
//	AD_light_init();				//AD模数转换初始化 
//	AD_smoke_init();	//
	ADC1_DMA_init();	//ADC1多通道+DMA转运初始化
	
	usart_send_string("姚乐毅\r\n");
	while(1){

		ADC_time_scale(50);

		printf("烟雾传感器电压 %.3f\r\n", ADC2V[0]);
		printf("光敏电阻电压 %.3f\r\n", ADC2V[1]);
		printf("CPU温度 %.3f\r\n", ADC2V[2]);
		
}

}

/**
  * @brief  根据光照强度控制RGB灯
  * @param  None
  * @retval None
  */
void light2rgb(void){
	float val = (((float)AD_light_Median_filter() / 4096) * 100);
	TIM_SetCompare1(TIM3, val);
}











