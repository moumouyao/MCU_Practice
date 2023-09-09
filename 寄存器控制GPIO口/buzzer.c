#include "buzzer.h"

/**
  * @brief 	��ʼ��������
  * @param  None
  * @retval None
  */
void buuzer_init(void){
	//����ʱ��
	RCC->APB2ENR |= 1 << 4; //ʹ�ܿ���GPIO_C��ʱ�� 
	GPIOC->CRL &= ~0xF;	//����
	GPIOC->CRL |= 3;				//��ֵ
	GPIOC->ODR |= 0;			
}

/**
  * @brief  ����������
  * @param  None
  * @retval None
  */
void buzzer_enable(void){
	GPIOC->ODR |= 1;
}

/**
  * @brief  �رշ�����
  * @param  None
  * @retval None
  */
void buzzer_disable(void){
	GPIOC->ODR = 0;
}