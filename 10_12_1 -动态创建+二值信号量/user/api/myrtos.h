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

/*开始任务配置*/
#define START_STK_SIZE 		128			  //任务堆栈大小	
#define START_TASK_PRIO		1				  //任务优先级


/*task1配置*/
#define TASK1_STK_SIZE 		128			  //任务堆栈大小	
#define TASK1_PRIO		2						  //任务优先级


/*task2配置*/
#define TASK2_STK_SIZE 		128			  //任务堆栈大小	
#define TASK2_PRIO		3						  //任务优先级


/*task1配置*/
#define TASK3_STK_SIZE 		128			  //任务堆栈大小	
#define TASK3_PRIO		3						  //任务优先级


void freertos_demo(void);

void start_task(void *pvParameters);

void task1(void *pvParameters);

void task2(void *pvParameters);

void task3(void *pvParameters);



#endif
