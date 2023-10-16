#include "my_mqtt.h"

extern esp esp8266;	//存放8266接收信息

//SER_VAL ser_val;
uint8_t ser_val[5][4] = {0};

/**
	* @brief  使用串口3，发送一个字符串
	* @param  char *str 需要发送的字符串
  * @retval None
  */
void usart3_send_string(char *str, uint16_t count){
	uint8_t i = 0;
	for(i = 0; i < count; i ++){
		usart_sendbit(USART3, str[i]);
		//printf("%c", str[i]);
	}
}

/**
  * @brief  检测服务器返回值
  * @param  uint16_t time	设置函数运行最大时间
  * @retval 0 连接成功		1 连接失败
  */
uint8_t check_server(char * str, uint16_t time){
	while(time--){
		if(esp8266.RX_flag == 1){
			esp8266.RX_flag = 0;
			if((esp8266.RX_data[0] == 0x20) && (esp8266.RX_data[1] == 0x02)){
//				esp8266.RX_count = 0;
//				memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
				return 0;
			}
			else if(strstr((char *)esp8266.RX_data, str) != NULL){
//				esp8266.RX_count = 0;
//				memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
				return 0;
			}
		}
		Delay_ms(1);
	}
	return 1;
}

/**
  * @brief  连接服务器函数
  * @param  None
  * @retval None
  */
	uint8_t mqtt_connect_server(void){
		
		//配置连接报文
		MQTTPacket_connectData options = MQTTPacket_connectData_initializer;	//通用参数设置默认值
//		options.cleansession = ;
		options.clientID.cstring = my_client_id;
//		options.keepAliveInterval = ;
//		options.MQTTVersion = ;
		options.password.cstring = my_password;
//		options.struct_id = ;
//		options.struct_version = ;
		options.username.cstring = my_username;
//		options.will = ;
//		options.willFlag = ;
		esp8266.tx_count = MQTTSerialize_connect(esp8266.tx_buf, 1024, &options);
		
		esp8266.RX_count = 0;
		memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
		//发送连接报文
		usart3_send_string((char *)esp8266.tx_buf, esp8266.tx_count);
		return check_server("success", 1000);
		
	}
	
/**
  * @brief  向服务器发送报文
  * @param  None
  * @retval 0 发送成功		1 发送失败
  */
uint8_t mqtt2server(char* cstr, char *payl, char * reply){
	
	MQTTString topicName = MQTTString_initializer;
	topicName.cstring = cstr;
	char* payload = payl;
	esp8266.tx_count = MQTTSerialize_publish(esp8266.tx_buf, 1024, 0, 0, 0, 0, topicName, (unsigned char *)payload, strlen(payload));
	esp8266.RX_count = 0;
	memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
	//发送连接报文
	usart3_send_string((char *)esp8266.tx_buf, esp8266.tx_count);
	printf("报文%s", esp8266.tx_buf);
	return check_server(reply, 2000);
}

/**
  * @brief  订阅服务器的属性设置
  * @param  None
  * @retval None
  */
void subscription_service(void){
	MQTTString topicFilters[2] = {0};
	int requestedQoSs[2] = {0};
	requestedQoSs[0] = 0;
	topicFilters[0].cstring = property_subscribe_cstring;
	topicFilters[1].cstring = time_subscribe_cstring;
	esp8266.tx_count = MQTTSerialize_subscribe(esp8266.tx_buf, 1024, 0, 0, 2, topicFilters, requestedQoSs);
	memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
	//发送连接报文
	usart3_send_string((char *)esp8266.tx_buf, esp8266.tx_count);
	//return check_server("?", 1000);
}
	

/**
  * @brief  服务器属性设置分析
  * @param  None
  * @retval None
  */
void subscription_analisys(void){
	char *property_val[] = {"temperature", "Humidity"};
	char *property_addr[2] = {NULL};
	if(esp8266.RX_flag == 1){
		esp8266.RX_flag = 0;
		for(int i = 0; i < 2; i++){
			property_addr[i] = strstr((char *)esp8266.RX_data, property_val[i]);
			
		}
		for(int i = 0; i < 2; i++){
			strncpy((char *)ser_val[i], property_addr[i] + strlen(property_val[i]) + 2, 4);
		}
		printf("温度 %s\r\n", ser_val[0]);
		printf("湿度 %s\r\n", ser_val[1]);
	}
}
	

/**
  * @brief  获取服务器时间
  * @param  None
  * @retval None
  */
uint32_t get_server_time(void){
	char *serverSendTime_addr = NULL;
	uint8_t  serverSendTime[20] = {0};
	printf("\r\n时间函数内\r\n");
	if(mqtt2server(time_publish_cstring, time_payload, "serverSendTime") == 0){
		printf("\r\njieshoubiaozhiwei:%d\r\n", esp8266.RX_flag);
		printf("\r\n时间数据发送成功\r\n");
		Delay_ms(2000);
			serverSendTime_addr = strstr((char *)esp8266.RX_data, "serverSendTime");
			strncpy((char *)serverSendTime, serverSendTime_addr + strlen("serverSendTime") + 3, 10);
		printf("%s\r\n",esp8266.RX_data);
		printf("\r\n*******************************\r\n");	
		printf("时间戳：%s\r\n", serverSendTime);
		printf("\r\n*******************************\r\n");
			return atoi((char *)serverSendTime);
	
	
								
}
	else{
		printf("时间函数内失败\r\n");
		return 1;
	}
}
