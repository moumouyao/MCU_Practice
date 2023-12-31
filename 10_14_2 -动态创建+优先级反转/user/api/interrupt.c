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
  * @brief  按键3,按键4中断服务函数	中断中恢复task1任务
  * @param  None
  * @retval None
  */
extern TaskHandle_t Task1_Handler;                    //任务句柄
void EXTI9_5_IRQHandler(void){
	 BaseType_t xYieldRequired;
	if(EXTI_GetITStatus(EXTI_Line5) == SET){
			if(k3 == 0){
				printf("在中断中恢复task1\r\n");
				xYieldRequired = xTaskResumeFromISR( Task1_Handler );
				if(xYieldRequired == pdTRUE){
					portYIELD_FROM_ISR( xYieldRequired );
				}
		}
		EXTI_ClearITPendingBit(EXTI_Line5);
		}
	if(EXTI_GetITStatus(EXTI_Line6) == SET){
		if(k4 == 0){
			
		}
		else{
			
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
		}
	
}

/**
  * @brief  定时器2中断服务函数
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		
		buzzer_init();
		//buzzer_turn(BUZZER_PORT, BUZZER_PIN);
		led_turn(GREEN_PORT, GREEN_PIN);
	}
	
}

/**
  * @brief  RTC寄存器秒中断，RGB灯反转
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void){
	if(RTC_GetITStatus(RTC_IT_SEC) == SET){
		RTC_ClearITPendingBit(RTC_IT_SEC);
		led_turn(LED2_PORT, LED2_PIN);
		//led_turn(GREEN_PORT, GREEN_PIN);
	}
	
}


/**
  * @brief  定时器6中断服务函数
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void){
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		//led_turn(LED1_PORT, LED1_PIN);
		printf("TIM6");
	}
}

/**
  * @brief  定时器7中断服务函数
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void){
	
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		//led_turn(LED2_PORT, LED2_PIN);
		printf("TIM7\r\n");
	}
}



