#include "led.h"

	/**
  * @brief  ��ʼ��LED��
  * @param  uint32_t t	LED�����
  * @retval None
  */
void led_init(uint32_t t){
	//����ʱ��
	RCC->APB2ENR |= 1 << 6; //ʹ�ܿ���GPIO_E��ʱ�� 1000000
	//�� CLR 8 �� 11 λ���ó� 0011
	GPIOE->CRL &= ~(0xF << (4 + t * 4));	//����
	GPIOE->CRL |= 3 << (4 + t * 4);				//��ֵ
	GPIOE->ODR |= (1 << (t + 1));			//���
}


	/**
  * @brief  ����LED��
  * @param  uint32_t t	LED�����
  * @retval None
  */
void led_enable(uint32_t t){
	GPIOE->ODR &= ~(1 << (t + 1));	//����͵�ƽ
}

	/**
  * @brief  Ϩ��LED��
  * @param  uint32_t t	LED�����
  * @retval None
  */
void led_disable(uint32_t t){
	GPIOE->ODR |= (1 << (t + 1));	//����ߵ�ƽ
}















