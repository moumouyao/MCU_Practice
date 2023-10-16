#include "my_mqtt.h"

extern esp esp8266;	//���8266������Ϣ

//SER_VAL ser_val;
uint8_t ser_val[5][4] = {0};

/**
	* @brief  ʹ�ô���3������һ���ַ���
	* @param  char *str ��Ҫ���͵��ַ���
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
  * @brief  ������������ֵ
  * @param  uint16_t time	���ú����������ʱ��
  * @retval 0 ���ӳɹ�		1 ����ʧ��
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
  * @brief  ���ӷ���������
  * @param  None
  * @retval None
  */
	uint8_t mqtt_connect_server(void){
		
		//�������ӱ���
		MQTTPacket_connectData options = MQTTPacket_connectData_initializer;	//ͨ�ò�������Ĭ��ֵ
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
		//�������ӱ���
		usart3_send_string((char *)esp8266.tx_buf, esp8266.tx_count);
		return check_server("success", 1000);
		
	}
	
/**
  * @brief  ����������ͱ���
  * @param  None
  * @retval 0 ���ͳɹ�		1 ����ʧ��
  */
uint8_t mqtt2server(char* cstr, char *payl, char * reply){
	
	MQTTString topicName = MQTTString_initializer;
	topicName.cstring = cstr;
	char* payload = payl;
	esp8266.tx_count = MQTTSerialize_publish(esp8266.tx_buf, 1024, 0, 0, 0, 0, topicName, (unsigned char *)payload, strlen(payload));
	esp8266.RX_count = 0;
	memset(esp8266.RX_data, 0, sizeof(esp8266.RX_data));
	//�������ӱ���
	usart3_send_string((char *)esp8266.tx_buf, esp8266.tx_count);
	printf("����%s", esp8266.tx_buf);
	return check_server(reply, 2000);
}

/**
  * @brief  ���ķ���������������
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
	//�������ӱ���
	usart3_send_string((char *)esp8266.tx_buf, esp8266.tx_count);
	//return check_server("?", 1000);
}
	

/**
  * @brief  �������������÷���
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
		printf("�¶� %s\r\n", ser_val[0]);
		printf("ʪ�� %s\r\n", ser_val[1]);
	}
}
	

/**
  * @brief  ��ȡ������ʱ��
  * @param  None
  * @retval None
  */
uint32_t get_server_time(void){
	char *serverSendTime_addr = NULL;
	uint8_t  serverSendTime[20] = {0};
	printf("\r\nʱ�亯����\r\n");
	if(mqtt2server(time_publish_cstring, time_payload, "serverSendTime") == 0){
		printf("\r\nʱ�����ݷ��ͳɹ�\r\n");
		Delay_ms(2000);
			serverSendTime_addr = strstr((char *)esp8266.RX_data, "serverSendTime");
			strncpy((char *)serverSendTime, serverSendTime_addr + strlen("serverSendTime") + 3, 10);
		printf("%s\r\n",esp8266.RX_data);
		printf("\r\n*******************************\r\n");	
		printf("ʱ�����%s\r\n", serverSendTime);
		printf("\r\n*******************************\r\n");
			return atoi((char *)serverSendTime);
	
	
								
}
	else{
		printf("ʱ�亯����ʧ��\r\n");
		return 1;
	}
}


/**
  * @brief  ��������ϴ�����
  * @param  None
  * @retval None
  */
void send_data2server(void){
	char send2server_data[1024] = {0};
	char temp1[16];
	float temp2;
	sprintf(temp1, "%d.%d", dht_data.tmp ,dht_data.tmp_flo);
	temp2 = atof(temp1);
//	printf("�¶�1��%f\r\n",temp2);
//	printf("�¶�2%f\r\n", (dht_data.tmp + (dht_data.tmp_flo / 10.0)));
	strcpy(send2server_data, property_payload);
	sprintf(send2server_data, property_payload, temp2, (float)dht_data.hum, kqm_data.CHO, kqm_data.CO2, kqm_data.VOC);
	printf("\r\n�ϴ����ݺ�����\r\n");
	printf("���� %s\r\n", send2server_data);
	if(mqtt2server(property_publish_cstring, send2server_data, "success") == 0){
		printf("\r\n�ϴ����ݳɹ�\r\n");
								
}
	else{
		printf("�ϴ�����ʧ��\r\n");
	}
}



/**
  * @brief  ����������Ϣ
  * @param  None
  * @retval None
  */
void whther_analisys(void){
	if(esp8266.RX_flag == 1){
		esp8266.RX_flag =0;
		printf("\r\n���յ�������\r\n%s\r\n��ӡ���\r\n", esp8266.RX_data);
		cJSON* cjson = cJSON_Parse((char *)esp8266.RX_data);//��JSON�ַ���ת����JSON�ṹ��
		if(cjson == NULL)						//�ж�ת���Ƿ�ɹ�
		{
			printf("cjson error...\r\n");
		}
		else
		{
			printf("%s\n",cJSON_Print(cjson));//����ɹ�����cJSON_Print��ӡ���
		}
		char *name = cJSON_GetObjectItem(cjson,"name")->valuestring;	//�����ַ���
		printf("city-------%s\r\n",name);
		int temperature = cJSON_GetObjectItem(cjson,"temperature")->valueint;	//��������
		printf("temperature---------%d\r\n",temperature);
								
	}
	

}

























