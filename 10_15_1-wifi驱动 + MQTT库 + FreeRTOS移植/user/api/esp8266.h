#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "stm32f10x.h"
#include "usart.h"
#include "string.h"
#include "Delay.h"
#include "my_mqtt.h"

#define IP_aliyum	"\"iot-060a7g0x.mqtt.iothub.aliyuncs.com\""
#define PORT_aliyun	1883
#define IP_seniverse	" api.m.taobao.com "
#define PORT_seniverse	80

typedef struct {
	uint8_t RX_data[2048];//���ڽ�������
	uint8_t	RX_count;			//���ڼ�����
	uint8_t RX_flag;			//���ձ�־λ
	uint8_t tx_buf[1024];	//���ͻ�����
	uint16_t tx_count;		//���ͼ�����
}esp;

extern esp esp8266;	//���8266������Ϣ

void esp8266_init(void);
void usart12usart3(void);
uint8_t soft2esp(char *AT_cmd, char *AT_retval, uint16_t AT_time);
uint8_t wifi_init(void);
uint32_t get_server_time(void);
uint8_t connect_seniverse(void);
#endif
