#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "stm32f10x.h"
#include "usart.h"
#include "string.h"
#include "Delay.h"
#include "my_mqtt.h"

typedef struct {
	uint8_t RX_data[1024];//串口接收数据
	uint8_t	RX_count;			//串口计数器
	uint8_t RX_flag;			//接收标志位
	uint8_t tx_buf[1024];	//发送缓冲区
	uint16_t tx_count;		//发送计数器
}esp;

extern esp esp8266;	//存放8266接收信息

void esp8266_init(void);
void usart12usart3(void);
uint8_t soft2esp(char *AT_cmd, char *AT_retval, uint16_t AT_time);
uint8_t wifi_init(void);
uint32_t get_server_time(void);
#endif
