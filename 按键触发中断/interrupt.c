#include "interrupt.h"
#include "buzzer.h"
#include "led.h"

uint8_t k1 = 0, k2 = 0, k3 = 0, k4 = 0;


/**
  * @brief  按键1中断服务函数，控制蜂鸣器
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void){
	buzzer_init();
	if(k1 == 0){
		buzzer_enable();
		k1++;
		EXTI_ClearITPendingBit(EXTI_Line0);
		return;
	}
	if(k1 == 1){
		buzzer_disable();
		k1 = 0;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
	
}

/**
  * @brief  按键2中断服务函数，控制流水灯
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void){
	RGB_init();
	if(k2 == 0){
		RGB_enable(RED);
		k2 = 1;
	}
	else{
		RGB_disable(RED);
		k2 = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}

/**
  * @brief  返回 EXTI4_IRQHandler 的操作结果
  * @param  None
  * @retval uint8_t val	k2的值
  */
uint8_t get_k2_val(void){
	uint16_t val = k2;
	return val;
}
/**
  * @brief  按键3,按键4中断服务函数
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void){
	RGB_init();
	if(EXTI_GetITStatus(EXTI_Line5) == SET){
			if(k3 == 0){
			RGB_enable(GREEN);
			k3 = 1;
		}
		else{
			RGB_disable(GREEN);
			k3 = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line5);
		}
	if(EXTI_GetITStatus(EXTI_Line6) == SET){
		if(k4 == 0){
			RGB_enable(BLUE);
			k4 = 1;
		}
		else{
			RGB_disable(BLUE);
			k4 = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
		}
	
}

