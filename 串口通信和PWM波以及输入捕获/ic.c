#include "ic.h"

void ic_init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	//������ʱ��4ʱ��
		//��ʼ��PB7
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//ѡ���ڲ���Ԫʱ��
	TIM_InternalClockConfig(TIM4);
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//����Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1;	//��ʱ1s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	//��ʼ�����벶��Ԫ
	TIM_ICInitTypeDef TIM_ICInitStruct = {0};
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;	//ʹ��ͨ��2
	TIM_ICInitStruct.TIM_ICFilter = 0XF;	//�˲�Ƶ��
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ش���
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//����Ƶ��ÿ�δ���
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;	//ֱ��
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	//ѡ���ģʽ����Դ
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI1FP1);
	//���ô�ģʽ
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM4, ENABLE);
}

uint32_t ic_get_freg(void){
	return 1000000 / TIM_GetCapture1(TIM4);
}
