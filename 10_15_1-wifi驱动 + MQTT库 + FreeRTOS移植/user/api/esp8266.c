#include "esp8266.h"

esp esp8266;	//存放8266接收信息

/**
  * @brief  初始化esp8266
	*						pb6	普通推挽输出
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
  * @brief  串口一转发给串口三
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
  * @brief  配置esp8266
  * @param  char *AT_cmd			AT指令
  * @param	char *AT_retval		输入参数，指令校验 
  * @param	uint16_t AT_time	操作时间
  * @retval 成功 0		失败 1	
  */
uint8_t soft2esp(char *AT_cmd, char *AT_retval, uint16_t AT_time){
	//清零
	esp8266.RX_count = 0;
	esp8266.RX_flag = 0;
	memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
	
	//发送
	usart_send_string(USART3, AT_cmd);
	
	//判断接收值
	while(AT_time--){
		if(esp8266.RX_flag == 1){
		//esp8266.RX_flag = 0;
		if(strstr((char *)esp8266.RX_data, AT_retval) != NULL){
			return 0;	//返回值正确，设置成功
		}
	}
		Delay_ms(1);
		
	}
	return 1;	//返回值不正确，设置失败
}

/**
  * @brief  esp远程连接服务器
  * @param  None
  * @retval 成功 0		失败 1
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
								printf("\r\n连接阿里云成功\r\n");
									rtc_init();
//								if(mqtt2server(property_publish_cstring, property_payload, "success") == 0){
//									printf("\r\n数据发送成功\r\n");
//									
//								}
//								else{
//									printf("\r\n数据发送失败\r\n");
//								}
//								if(mqtt2server(time_publish_cstring, time_payload, "serverSendTime") == 0){
//										printf("\r\n时间数据发送成功\r\n");
//								}
//								
							}
							else{
								printf("\r\n连接阿里云失败\r\n");
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
  * @brief  esp远程连接服务器
  * @param  None
  * @retval 成功 0		失败 1
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
							printf("开始收发数据\r\n");
	
						
							if(soft2esp(send_buf, "temperature", 2000) == 0){
								printf("获取天气成功\r\n");
								
								return 0;
							}
							else{
								printf("获取天气失败\r\n");
							}

						}
						else{
							printf("开始收发数据失败\r\n");
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



