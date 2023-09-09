#include "buzzer.h"

/**
  * @brief 	初始化蜂鸣器
  * @param  None
  * @retval None
  */
void buuzer_init(void){
	//开启时钟
	RCC->APB2ENR |= 1 << 4; //使能开启GPIO_C的时钟 
	GPIOC->CRL &= ~0xF;	//清零
	GPIOC->CRL |= 3;				//赋值
	GPIOC->ODR |= 0;			
}

/**
  * @brief  开启蜂鸣器
  * @param  None
  * @retval None
  */
void buzzer_enable(void){
	GPIOC->ODR |= 1;
}

/**
  * @brief  关闭蜂鸣器
  * @param  None
  * @retval None
  */
void buzzer_disable(void){
	GPIOC->ODR = 0;
}