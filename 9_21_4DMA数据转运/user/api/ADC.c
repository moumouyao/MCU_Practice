#include "ADC.h"

/**
  * @brief  配置PA5接收数模转换后的数据
  * @param  None
  * @retval None
  */
void AD_init(void){
	//配置ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	//配置PA0
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		//配置ADC1 通道0 序列1 55.5个ADC时钟周期
		ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	
	//结构体初始化ADC1
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//独立工作模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不需要外部中断
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;	//关闭连续转换模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;	//进制扫描模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//采样通道时为1
	ADC_Init(ADC1, &ADC_InitStruct);
	
	//开启ADC电源
	ADC_Cmd(ADC1, ENABLE);
	
	//对ADC进行校准
	ADC_ResetCalibration(ADC1);	//复位校准	置1
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位等待置0
	ADC_StartCalibration(ADC1);		//启动校准
	while(ADC_GetCalibrationStatus(ADC1));	//等待校准完成
}

/**
  * @brief  获取模数转换后的值
  * @param  None
  * @retval None
  */
uint16_t AD_get_val(void){
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}










