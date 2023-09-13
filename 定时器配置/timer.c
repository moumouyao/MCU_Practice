#include "timer.h"

/**
  * @brief  初始化定时器6，实现1us延迟
  * @param  None
  * @retval None
  */
void time6_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);	//开启定时器6时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0X0;	//时钟分割 默认0
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//计数方式
	TIM_TimeBaseInitStruct.TIM_Period = 1 - 1;	//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;	//预分频值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	//使能更新中断
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	//初始化NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//使能定时器
	TIM_Cmd(TIM6, ENABLE);
}

/**
  * @brief  初始化定时器7，实现1ms延迟
  * @param  None
  * @retval None
  */
void time7_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);	//开启定时器7时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0X0;	//时钟分割 默认0
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//计数方式
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;	//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;	//预分频值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);
	
	//使能更新中断
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	//初始化NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//使能定时器
	TIM_Cmd(TIM7, ENABLE);
}

/**
  * @brief  初始化定时器2，实现1s延迟
  * @param  None
  * @retval None
  */
void time2_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//开启定时器7时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0X0;	//时钟分割 默认0
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//计数方式
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;	//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;	//预分频值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//使能更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//初始化NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//使能定时器
	TIM_Cmd(TIM2, ENABLE);
}



