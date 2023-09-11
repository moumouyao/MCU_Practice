#include "key.h"
#include "Delay.h"
/**
  * @brief  初始化按键GPIO口
  * @param  None
  * @retval None
  */
void key_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//将PA0初始化位下拉输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//将PC4~PC6初始化位上拉输入模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  * @brief  按键检测
  * @param  None
  * @retval 按键按下返回对应的键值，没有按键按下返回0
  */
uint8_t key_get_num(void){
	uint8_t keynum = 0;
	//按键1按下
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
		Delay_ms(5);	//消抖
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) != 1){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1);
		Delay_ms(5);
		keynum = 1;
	}
	//按键2按下
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0){
		Delay_ms(5);	//消抖
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) != 0){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0);
		Delay_ms(5);
		keynum = 2;
	}
		//按键3按下
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0){
		Delay_ms(20);	//消抖
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != 0){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0);
		Delay_ms(5);
		keynum = 3;
	}
			//按键4按下
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == 0){
		Delay_ms(5);	//消抖
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != 0){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == 0);
		Delay_ms(5);
		keynum = 4;
	}
	return keynum;
}


















