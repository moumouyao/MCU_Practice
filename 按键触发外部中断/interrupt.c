#include "interrupt.h"
#include "buzzer.h"
#include "led.h"

uint8_t k1 = 0, k2 = 0, k3 = 0, k4 = 0;


/**
  * @brief  ����1�жϷ����������Ʒ�����
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
  * @brief  ����2�жϷ�������������ˮ��
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void){
	if(k2 == 0){
		k2++;
		EXTI_ClearITPendingBit(EXTI_Line4);
		waterfall_light();
		return;
	}
	if(k2 == 1){
		buzzer_disable();
		k2 = 0;
		led_disable(LED1);led_disable(LED2);led_disable(LED3);led_disable(LED4);
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
	
}

/**
  * @brief  ����3,����4�жϷ�����
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line5) == SET){
		
	}
	if(EXTI_GetITStatus(EXTI_Line6) == SET){
		
	}
}

