#include "key.h"
#include "Delay.h"
/**
  * @brief  ��ʼ������GPIO��
  * @param  None
  * @retval None
  */
void key_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//��PA0��ʼ��λ��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//��PC4~PC6��ʼ��λ��������ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  * @brief  �������
  * @param  None
  * @retval �������·��ض�Ӧ�ļ�ֵ��û�а������·���0
  */
uint8_t key_get_num(void){
	uint8_t keynum = 0;
	//����1����
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
		Delay_ms(5);	//����
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) != 1){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1);
		Delay_ms(5);
		keynum = 1;
	}
	//����2����
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0){
		Delay_ms(5);	//����
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) != 0){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0);
		Delay_ms(5);
		keynum = 2;
	}
		//����3����
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0){
		Delay_ms(20);	//����
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != 0){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0);
		Delay_ms(5);
		keynum = 3;
	}
			//����4����
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == 0){
		Delay_ms(5);	//����
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != 0){
			return 0;
		}
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == 0);
		Delay_ms(5);
		keynum = 4;
	}
	return keynum;
}


















