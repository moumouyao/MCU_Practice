#ifndef __MYRTOS_H_
#define __MYRTOS_H_

#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "su_03t.h"
#include "kqm.h"
#include "dht11.h"
#include "ADC.h"
#include "key.h"
#include "RTC.h"
#include "my_lcd.h"
#include "my_spi_flash.h"
#include "esp8266.h"
/**********************��������******************************/
/*��ʼ��������*/
#define START_STK_SIZE 		512			  //�����ջ��С	
#define START_TASK_PRIO		1				  //�������ȼ�


/*task1����*/
#define TASK1_STK_SIZE 		512			  //�����ջ��С	
#define TASK1_PRIO		2						  //�������ȼ�


/*task2����*/
#define TASK2_STK_SIZE 		128			  //�����ջ��С	
#define TASK2_PRIO		3						  //�������ȼ�


/*task3����*/
#define TASK3_STK_SIZE 		512			  //�����ջ��С	
#define TASK3_PRIO		2						  //�������ȼ�

/*task4����*/
#define TASK4_STK_SIZE 		128			  //�����ջ��С	
#define TASK4_PRIO		5						  //�������ȼ�

/*task5����*/
#define TASK5_STK_SIZE 		512			  //�����ջ��С	
#define TASK5_PRIO		6						  //�������ȼ�

/*task5����*/
#define TASK6_STK_SIZE 		512			  //�����ջ��С	
#define TASK6_PRIO		7						  //�������ȼ�
/************************************************************/

void freertos_demo(void);

void start_task(void *pvParameters);

void task1(void *pvParameters);

void task2(void *pvParameters);

void task3(void *pvParameters);

void task4(void *pvParameters);

void task5(void *pvParameters);

void task6(void *pvParameters);


#endif
