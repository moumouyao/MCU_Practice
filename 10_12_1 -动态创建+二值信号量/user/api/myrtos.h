#ifndef __MYRTOS_H_
#define __MYRTOS_H_

#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "Delay.h"
#include "queue.h"
#include "semphr.h"

/*��ʼ��������*/
#define START_STK_SIZE 		128			  //�����ջ��С	
#define START_TASK_PRIO		1				  //�������ȼ�


/*task1����*/
#define TASK1_STK_SIZE 		128			  //�����ջ��С	
#define TASK1_PRIO		2						  //�������ȼ�


/*task2����*/
#define TASK2_STK_SIZE 		128			  //�����ջ��С	
#define TASK2_PRIO		3						  //�������ȼ�


/*task1����*/
#define TASK3_STK_SIZE 		128			  //�����ջ��С	
#define TASK3_PRIO		3						  //�������ȼ�


void freertos_demo(void);

void start_task(void *pvParameters);

void task1(void *pvParameters);

void task2(void *pvParameters);

void task3(void *pvParameters);



#endif
