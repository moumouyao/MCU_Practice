#include "ic.h"

void ic_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	//开启定时器4时钟
		//初始化PB7
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//选择内部单元时钟
	TIM_InternalClockConfig(TIM4);
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//不分频
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1;	//定时1s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	//初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStruct = {0};
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;	//使用通道2
	TIM_ICInitStruct.TIM_ICFilter = 0XF;	//滤波频率
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿触发
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//不分频，每次触发
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;	//直连
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	//选择从模式触发源
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI1FP1);
	//配置从模式
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM4, ENABLE);
}

uint32_t ic_get_freg(void){
	return 1000000 / TIM_GetCapture1(TIM4);
}
