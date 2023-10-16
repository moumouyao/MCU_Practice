#include "esp8266.h"

esp esp8266;	//���8266������Ϣ

/**
  * @brief  ��ʼ��esp8266
	*						pb6	��ͨ�������
  * @param  None
  * @retval None
  */
void esp8266_init(void){
		usart3_init();
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
		GPIO_SetBits(GPIOE, GPIO_Pin_6);
}

/**
  * @brief  ����һת����������
  * @param  None
  * @retval None
  */
void usart12usart3(void){
	if(usart_get_RXflag() == 1){
			if(strstr(usart_RX_str_packet, "AT") != NULL){
				printf("%s", usart_RX_str_packet);
				usart_send_string(USART3, usart_RX_str_packet);
				//usart_send_string(USART1, usart_RX_str_packet);
				memset(usart_RX_str_packet, 0, sizeof(usart_RX_str_packet));
			}
		}
}

/**
  * @brief  ����esp8266
  * @param  char *AT_cmd			ATָ��
  * @param	char *AT_retval		���������ָ��У�� 
  * @param	uint16_t AT_time	����ʱ��
  * @retval �ɹ� 0		ʧ�� 1	
  */
uint8_t soft2esp(char *AT_cmd, char *AT_retval, uint16_t AT_time){
	//����
	esp8266.RX_count = 0;
	esp8266.RX_flag = 0;
	memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
	
	//����
	usart_send_string(USART3, AT_cmd);
	
	//�жϽ���ֵ
	while(AT_time--){
		if(esp8266.RX_flag == 1){
		//esp8266.RX_flag = 0;
		if(strstr((char *)esp8266.RX_data, AT_retval) != NULL){
			return 0;	//����ֵ��ȷ�����óɹ�
		}
	}
		Delay_ms(1);
		
	}
	return 1;	//����ֵ����ȷ������ʧ��
}

/**
  * @brief  espԶ�����ӷ�����
  * @param  None
  * @retval �ɹ� 0		ʧ�� 1
  */
uint8_t wifi_init(void){
	printf("\r\n");
	if(soft2esp("AT\r\n","OK",1000)==0)
	{
		if(soft2esp("AT+CWMODE=1\r\n","OK",1000)==0)
		{
			if(soft2esp("AT+CWJAP=\"moumouyao\",\"12345678\"\r\n","OK",10000)==0)
			{
				if(soft2esp("AT+CIPMODE=1\r\n","OK",1000)==0)
				{
					if(soft2esp("AT+CIPSTART=\"TCP\",\"iot-060a7g0x.mqtt.iothub.aliyuncs.com\",1883\r\n","OK",5000)==0)
					{
						printf("connect to server successed\r\n");
						if(soft2esp("AT+CIPSEND\r\n",">",1000)==0)
						{
							if(mqtt_connect_server() == 0){
								printf("\r\n���Ӱ����Ƴɹ�\r\n");
									rtc_init();
//								if(mqtt2server(property_publish_cstring, property_payload, "success") == 0){
//									printf("\r\n���ݷ��ͳɹ�\r\n");
//									
//								}
//								else{
//									printf("\r\n���ݷ���ʧ��\r\n");
//								}
//								if(mqtt2server(time_publish_cstring, time_payload, "serverSendTime") == 0){
//										printf("\r\nʱ�����ݷ��ͳɹ�\r\n");
//								}
//								
							}
							else{
								printf("\r\n���Ӱ�����ʧ��\r\n");
								return 1;
							}
							
							return 0;
						
						}
						else{
							return 1;
						}
					
					}
					else{
						printf("connect to server err\r\n");
						return 1;
					}
				}
				else{
					return 1;
				}
			}
			else
			{
				printf("wifi err\r\n");
				return 1;
			}
		}
		else{
		return 1;
		}
	}
	else{
		return 1;
	}
}


/**
  * @brief  espԶ�����ӷ�����
  * @param  None
  * @retval �ɹ� 0		ʧ�� 1
  */
uint8_t connect_seniverse(void){
	printf("\r\n");
	char send_buf[1024] = "GET https://api.seniverse.com/v3/weather/now.json?key=StvgScKh2NewX_quB&location=zhengzhou&language=en&unit=c\r\n";
	char buf[32] = {0};
	soft2esp("+++","OK",1000);
	printf("AT+CIPCLOSE********\r\n");
	soft2esp("AT+CIPCLOSE\r\n","OK",1000);
	if(soft2esp("AT\r\n","OK",1000)==0)
	{
		if(soft2esp("AT+CWMODE=1\r\n","OK",1000)==0)
		{
			if(soft2esp("AT+CWJAP=\"moumouyao\",\"12345678\"\r\n","OK",10000)==0)
			{
				if(soft2esp("AT+CIPMODE=1\r\n","OK",1000)==0)
				{
					if(soft2esp("AT+CIPSTART=\"TCP\",\"api.seniverse.com\",80\r\n","OK",5000)==0)
					{
						printf("connect to server successed\r\n");
						//snprintf(buf, sizeof(send_buf), "AT+CIPSEND=%d\r\n", strlen(send_buf));
						if(soft2esp("AT+CIPSEND\r\n",">",1000)==0)
						{
							printf("��ʼ�շ�����\r\n");
	
						
							if(soft2esp(send_buf, "temperature", 2000) == 0){
								printf("��ȡ�����ɹ�\r\n");
								
								return 0;
							}
							else{
								printf("��ȡ����ʧ��\r\n");
							}

						}
						else{
							printf("��ʼ�շ�����ʧ��\r\n");
							return 1;
						}
					
					}
					else{
						printf("connect to server err\r\n");
						return 1;
					}
				}
				else{
					printf("***********1\r\n");
					return 1;
				}
			}
			else
			{
				printf("wifi err\r\n");
				return 1;
			}
		}
		else{
			printf("***********2\r\n");
		return 1;
		}
	}
	else{
		printf("***********3\r\n");
		return 1;
	}

	
}



