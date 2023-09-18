#include "su_03t.h"

uint8_t usart_su_RXdata;		//��Ž������ݼĴ�����ֵ
uint8_t usart_su_RXflag;		//�������ݱ�־λ
uint8_t usart_su_RXpacket[5] = {0};	//hex���ݰ���������
uint8_t usart_su_TXpacket[5] = {0xAA, 0x55, 0x04};	//hex���ݰ���������

/**
  * @brief  ���ô��� PC10 ���͸�������    PC11 ���ո���ģʽ  
  * @param  None
  * @retval None
  */
void su_o3t_init(void){
	//��ʼ��GPIO��
	//PA9��������
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PA10����
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//���ڳ�ʼ��
	//��������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	//��ʼ������
	USART_InitTypeDef USART_InitStruct = {0};
	USART_InitStruct.USART_BaudRate = 115200;	//���ò�����
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ʧ��
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ѡ�񴮿ڷ���ģʽ�ͽ���ģʽ
	USART_InitStruct.USART_Parity = USART_Parity_No;	//����ҪУ��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	//һλֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	//�ֳ�ѡ��8λ
	USART_Init(UART4, &USART_InitStruct);
	
	//���������ж�
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
		//��ʼ��NVIC
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitTypeDef NVIC_InitStruct;
  	NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
  	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  	NVIC_Init(&NVIC_InitStruct);
	
	//ʹ�ܴ���
	USART_Cmd(UART4, ENABLE);
}

/**
  * @brief  ����һ�жϷ�����������һ���ֽڵ����ݣ�������־λ��1
	*       hex���ݰ�		����  5 		��ʼ��־λ 0xAA 
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void){
	static uint8_t RX_su_State = 0;
	static uint8_t su_pRXpacket = 0;
	//usart_init();
	//usart_send_string("y");
	if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET){
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		
		usart_su_RXdata = USART_ReceiveData(UART4);
		//�жϽ��յ����ݰ�ͷ
		if(RX_su_State == 0){	
			if(usart_su_RXdata == 0XAA){	//���յ���ʹhex�ļ�
				usart_su_RXpacket[0] = usart_su_RXdata;
				RX_su_State = 1;	
				su_pRXpacket = 1;
			}
		}
			else if(RX_su_State == 1){	//����hex�ļ�������
				usart_su_RXpacket[su_pRXpacket] = usart_su_RXdata;
				su_pRXpacket++;
				if(su_pRXpacket >= 4){		//�������ݰ�����λ4������
					RX_su_State = 2;
				}
			}
			else if(RX_su_State == 2){	//�ж�hex���ݰ�������־λ
				if(usart_su_RXdata == 0XAA){
					usart_su_RXpacket[su_pRXpacket] = usart_su_RXdata;
					RX_su_State = 0;
					usart_su_RXflag = 1;
				}
				else{
					RX_su_State = 0;
					usart_su_RXflag = 0;
					usart_su_RXpacket[su_pRXpacket] = usart_su_RXdata;
					usart_send_string("$");
				}
			}
	}
}

/**
  * @brief  ��ȡusart_su_flag��ֵ
  * @param  None
  * @retval usart_su_RXflag ����2���ձ�־λ 
  */
uint8_t usart_get_su_RXflag(void){
	if(usart_su_RXflag == 1){
		usart_su_RXflag = 0;
		return 1;
	}
	return 0;
}

void vioce_analysis(void){
	usart_send_array(usart_su_RXpacket, 5);
	if(usart_get_su_RXflag() == 1){
		if(usart_su_RXpacket[2] == 0x02){
			led_enable(LED1);
		}
		else if(usart_su_RXpacket[2] == 0x03){
			led_disable(LED1);
		}
		else if(usart_su_RXpacket[2] == 0x04){
			usart_send2su_array(usart_su_TXpacket,5);
		}
	}
}

/**
	* @brief  ����һ������
	* @param  uint8_t *array ��Ҫ���͵�����
	* @param	uint16_t len	���͵����鳤��
  * @retval None
  */
void usart_send2su_array(uint8_t *array, uint16_t len){
	uint16_t i = 0;
	for(i = 0; i < len; i++){
		usart_send2su_bit(array[i]);
	}
}

/**
  * @brief  ���͵����ֽ�
* @param  uint8_t data	��Ҫ���͵��ֽ�
  * @retval None
  */
void usart_send2su_bit(uint8_t data){
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) != 1); //�ȴ���һ�����ݷ������
	USART_SendData(UART4, data);	//��������
}
