#include "timer.h"

/**
  * @brief  ��ʼ����ʱ��6��ʵ��1us�ӳ�
  * @param  None
  * @retval None
  */
void time6_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);	//������ʱ��6ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0X0;	//ʱ�ӷָ� Ĭ��0
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//������ʽ
	TIM_TimeBaseInitStruct.TIM_Period = 1 - 1;	//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;	//Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	//ʹ�ܸ����ж�
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	//��ʼ��NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM6, ENABLE);
}

/**
  * @brief  ��ʼ����ʱ��7��ʵ��1ms�ӳ�
  * @param  None
  * @retval None
  */
void time7_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);	//������ʱ��7ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0X0;	//ʱ�ӷָ� Ĭ��0
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//������ʽ
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;	//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;	//Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);
	
	//ʹ�ܸ����ж�
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	//��ʼ��NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM7, ENABLE);
}

/**
  * @brief  ��ʼ����ʱ��2��ʵ��1s�ӳ�
  * @param  None
  * @retval None
  */
void time2_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//������ʱ��7ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0X0;	//ʱ�ӷָ� Ĭ��0
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//������ʽ
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;	//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;	//Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//ʹ�ܸ����ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//��ʼ��NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2, ENABLE);
}



