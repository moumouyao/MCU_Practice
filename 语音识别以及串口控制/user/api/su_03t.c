#include "su_03t.h"

uint8_t usart_su_RXdata;		//存放接收数据寄存器的值
uint8_t usart_su_RXflag;		//接收数据标志位
uint8_t usart_su_RXpacket[5] = {0};	//hex数据包接收数组
uint8_t usart_su_TXpacket[5] = {0xAA, 0x55, 0x04};	//hex数据包接收数组

/**
  * @brief  配置串口 PC10 发送复用推挽    PC11 接收浮空模式  
  * @param  None
  * @retval None
  */
void su_o3t_init(void){
	//初始化GPIO口
	//PA9复用推挽
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PA10浮空
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//串口初始化
	//开启串口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	//初始化串口
	USART_InitTypeDef USART_InitStruct = {0};
	USART_InitStruct.USART_BaudRate = 115200;	//设置波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制失能
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//选择串口发送模式和接收模式
	USART_InitStruct.USART_Parity = USART_Parity_No;	//不需要校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	//一位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	//字长选择8位
	USART_Init(UART4, &USART_InitStruct);
	
	//开启串口中断
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
		//初始化NVIC
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitTypeDef NVIC_InitStruct;
  	NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
  	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  	NVIC_Init(&NVIC_InitStruct);
	
	//使能串口
	USART_Cmd(UART4, ENABLE);
}

/**
  * @brief  串口一中断服务函数，接收一个字节的数据，并将标志位置1
	*       hex数据包		长度  5 		开始标志位 0xAA 
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
		//判断接收的数据包头
		if(RX_su_State == 0){	
			if(usart_su_RXdata == 0XAA){	//接收到的使hex文件
				usart_su_RXpacket[0] = usart_su_RXdata;
				RX_su_State = 1;	
				su_pRXpacket = 1;
			}
		}
			else if(RX_su_State == 1){	//接收hex文件的内容
				usart_su_RXpacket[su_pRXpacket] = usart_su_RXdata;
				su_pRXpacket++;
				if(su_pRXpacket >= 4){		//接收数据包长度位4的数据
					RX_su_State = 2;
				}
			}
			else if(RX_su_State == 2){	//判断hex数据包结束标志位
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
  * @brief  获取usart_su_flag的值
  * @param  None
  * @retval usart_su_RXflag 串口2接收标志位 
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
	* @brief  发送一个数组
	* @param  uint8_t *array 需要发送的数组
	* @param	uint16_t len	发送的数组长度
  * @retval None
  */
void usart_send2su_array(uint8_t *array, uint16_t len){
	uint16_t i = 0;
	for(i = 0; i < len; i++){
		usart_send2su_bit(array[i]);
	}
}

/**
  * @brief  发送单个字节
* @param  uint8_t data	需要发送的字节
  * @retval None
  */
void usart_send2su_bit(uint8_t data){
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) != 1); //等待上一次数据发送完成
	USART_SendData(UART4, data);	//发送数据
}
