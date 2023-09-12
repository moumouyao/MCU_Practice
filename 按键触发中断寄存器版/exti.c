#include "exti.h"
#include "buzzer.h"

uint8_t k1 = 0, k2 = 0, k3 = 0, k4 = 0;
/**
  * @brief  ��PA0���ó��ⲿ�ж� 
	*						��ռ���ȼ� 0		��Ӧ���ȼ� 0
  * @param  None
  * @retval None
  */
	void key1_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//��������ʱ��
		AFIO->EXTICR[0] &= ~(0XF << 0);	//����PA0��Ӧ���ж���0
		EXTI->IMR |= 1 << 0;	//����PA0���ж����μĴ���
		EXTI->RTSR |= 1 << 0;	//���������ش���
		EXTI->FTSR  &= 0 << 0;	//�ر��½��ش���
		EXTI->PR |= 1 << 0; //��������־λ
		NVIC_SetPriorityGrouping(2);
		NVIC_SetPriority(EXTI0_IRQn, 0);	//��ռ���ȼ� 0  ��Ӧ���ȼ� 0
		NVIC_EnableIRQ(EXTI0_IRQn);		//ʹ���ⲿ�ж�0
	}
	
	/**
    * @brief  ����1�жϴ�����
    * @param  None
    * @retval �������£���־λk1��ת
    */
	void EXTI0_IRQHandler(void){
		if((EXTI->PR & 1 << 0) == 1){
			EXTI->PR |= 1 << 0; //��������־λ
			if(k1 ==  0){
				k1 = 1;
			}
			else{
				k1 = 0;
			}
			
		}
	}
	
	/**
  * @brief  ��PC0���ó��ⲿ�ж� 
	*						��ռ���ȼ� 0		��Ӧ���ȼ� 0
  * @param  None
  * @retval None
  */
	void key2_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//��������ʱ��
		AFIO->EXTICR[1] &= ~(0XF << 0);	//����PC4	��Ӧ���ж���4
		AFIO->EXTICR[1] |= (0X2  << 0);
		EXTI->IMR |= 1 << 4;	//����PC4���ж����μĴ���
		EXTI->FTSR  |= 1 << 4;	//�����½��ش���
		EXTI->PR |= 1 << 4; //��������־λ
		NVIC_SetPriority(EXTI4_IRQn, 0);	//��ռ���ȼ� 0  ��Ӧ���ȼ� 0
		NVIC_EnableIRQ(EXTI4_IRQn);		//ʹ���ⲿ�ж�0
	}
	
	/**
    * @brief  ����2�жϴ�����
    * @param  None
    * @retval �������£���־λk2��ת
    */
	void EXTI4_IRQHandler(void){
		if((EXTI->PR & 1 << 4) != 0){
			EXTI->PR |= 1 << 4; //��������־λ
			if(k2 ==  0){
				k2 = 1;
			}
			else{
				k2 = 0;
			}
			
		}
	}
	
		/**
  * @brief  ��PC5���ó��ⲿ�ж� 
	*						��ռ���ȼ� 0		��Ӧ���ȼ� 0
  * @param  None
  * @retval None
  */
	void key3_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//��������ʱ��
		AFIO->EXTICR[1] &= ~(0XF << 4);	//����PC5	��Ӧ���ж���4
		AFIO->EXTICR[1] |= (0X2  << 4);
		EXTI->IMR |= 1 << 5;	//����PC5���ж����μĴ���
		EXTI->FTSR  |= 1 << 5;	//�����½��ش���
		EXTI->PR |= 1 << 5; //��������־λ
		NVIC_SetPriority(EXTI9_5_IRQn, 0);	//��ռ���ȼ� 0  ��Ӧ���ȼ� 0
		NVIC_EnableIRQ(EXTI9_5_IRQn);		//ʹ���ⲿ�ж�0
	}
	
			/**
  * @brief  ��PC6���ó��ⲿ�ж� 
	*						��ռ���ȼ� 0		��Ӧ���ȼ� 0
  * @param  None
  * @retval None
  */
	void key4_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//��������ʱ��
		AFIO->EXTICR[1] &= ~(0XF << 8);	//����PC6	��Ӧ���ж���6
		AFIO->EXTICR[1] |= (0X2  << 8);
		EXTI->IMR |= 1 << 6;	//����PC6���ж����μĴ���
		EXTI->FTSR  |= 1 << 6;	//�����½��ش���
		EXTI->PR |= 1 << 6; //��������־λ
		NVIC_SetPriority(EXTI9_5_IRQn, 0);	//��ռ���ȼ� 0  ��Ӧ���ȼ� 0
		NVIC_EnableIRQ(EXTI9_5_IRQn);		//ʹ���ⲿ�ж�0
	}
	
	/**
    * @brief  ����3����4�жϴ�����
    * @param  None
    * @retval None
    */
	void EXTI9_5_IRQHandler(void){
		if((EXTI->PR & 1 << 5) != 0){		//�ⲿ�ж�5����
			EXTI->PR |= 1 << 5; //��������־λ
			if(k3 ==  0){
				k3 = 1;
			}
			else{
				k3 = 0;
			}
			
		}
		if((EXTI->PR & 1 << 6) != 0){		//�ⲿ�ж�5����
			EXTI->PR |= 1 << 6; //��������־λ
			if(k4 ==  0){
				k4 = 1;
			}
			else{
				k4 = 0;
			}
			
		}
	}
	
	/**
    * @brief  ���ذ����ı�־λ
    * @param  keyx Ҫ���صİ��� 1 2 3 4
    * @retval val	����1��־λ
    */
	uint8_t get_key_val(uint8_t key){
		switch(key){
			case KEY1: return k1;
			case KEY2: return k2;
			case KEY3: return k3;
			case KEY4: return k4;
			default: return 0;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
