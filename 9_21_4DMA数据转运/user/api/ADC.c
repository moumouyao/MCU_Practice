#include "ADC.h"

/**
  * @brief  ����PA5������ģת���������
  * @param  None
  * @retval None
  */
void AD_init(void){
	//����ADC1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	//����PA0
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		//����ADC1 ͨ��0 ����1 55.5��ADCʱ������
		ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	
	//�ṹ���ʼ��ADC1
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//��������ģʽ
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//�����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//����Ҫ�ⲿ�ж�
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;	//�ر�����ת��ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;	//����ɨ��ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;//����ͨ��ʱΪ1
	ADC_Init(ADC1, &ADC_InitStruct);
	
	//����ADC��Դ
	ADC_Cmd(ADC1, ENABLE);
	
	//��ADC����У׼
	ADC_ResetCalibration(ADC1);	//��λУ׼	��1
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λ�ȴ���0
	ADC_StartCalibration(ADC1);		//����У׼
	while(ADC_GetCalibrationStatus(ADC1));	//�ȴ�У׼���
}

/**
  * @brief  ��ȡģ��ת�����ֵ
  * @param  None
  * @retval None
  */
uint16_t AD_get_val(void){
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}










