#include "led.h"

	/**
  * @brief  初始化LED灯
  * @param  uint32_t t	LED灯序号
  * @retval None
  */
void led_init(uint32_t t){
	//开启时钟
	RCC->APB2ENR |= 1 << 6; //使能开启GPIO_E的时钟 1000000
	//把 CLR 8 到 11 位设置成 0011
	GPIOE->CRL &= ~(0xF << (4 + t * 4));	//清零
	GPIOE->CRL |= 3 << (4 + t * 4);				//赋值
	GPIOE->ODR |= (1 << (t + 1));			//灭灯
}


	/**
  * @brief  点亮LED灯
  * @param  uint32_t t	LED灯序号
  * @retval None
  */
void led_enable(uint32_t t){
	GPIOE->ODR &= ~(1 << (t + 1));	//输出低电平
}

	/**
  * @brief  熄灭LED灯
  * @param  uint32_t t	LED灯序号
  * @retval None
  */
void led_disable(uint32_t t){
	GPIOE->ODR |= (1 << (t + 1));	//输出高电平
}















