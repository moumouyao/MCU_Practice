#include "myrtos.h"
/*任务函数相关配置********************************************************************/

/*开始任务*/
TaskHandle_t StartTask_Handler;			//任务句柄
StackType_t start_task_stack[START_STK_SIZE];
StaticTask_t start_task_tcb;

/*任务1*/
TaskHandle_t Task1_Handler;					//任务句柄
StackType_t task1_stack[TASK1_STK_SIZE];
StaticTask_t task1_tcb;

/*任务2*/
TaskHandle_t Task2_Handler;					//任务句柄
StackType_t task2_stack[TASK2_STK_SIZE];
StaticTask_t task2_tcb;

/*任务3*/
TaskHandle_t Task3_Handler;					//任务句柄
StackType_t task3_stack[TASK3_STK_SIZE];
StaticTask_t task3_tcb;
/**************************************************************************************/

/**
  * @brief  静态空闲任务内存分配
  * @param  StaticTask_t **ppxIdleTaskTCBBuffer		空闲任务 任务控制块
  * @param 	StackType_t **ppxIdleTaskStackBuffer	空闲任务的任务堆栈
  * @param 	uint32_t *pulIdleTaskStackSize 
  * @retval None
  */
	StaticTask_t idle_task_tcb;
	StackType_t idle_task_stack[configMINIMAL_STACK_SIZE];
	void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, 
																			StackType_t **ppxIdleTaskStackBuffer, 
																			uint32_t *pulIdleTaskStackSize )/*lint !e526 Symbol not defined as it is an application callback. */
{
	*ppxIdleTaskTCBBuffer = &idle_task_tcb;
	*ppxIdleTaskStackBuffer = idle_task_stack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


/**
  * @brief  软件定时器内存分配
  * @param  StaticTask_t **ppxTimerTaskTCBBuffer		软件定时器任务控制块 																
  * @param  StackType_t **ppxTimerTaskStackBuffer		软件定时器任务堆栈 																		 
  * @param  uint32_t *pulTimerTaskStackSize					堆栈大小
* @retval None
  */
	StaticTask_t timer_task_tcb;
	StackType_t timer_task_stack[configTIMER_TASK_STACK_DEPTH];
	void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, 
																			 StackType_t **ppxTimerTaskStackBuffer, 
																			 uint32_t *pulTimerTaskStackSize )
{
	*ppxTimerTaskTCBBuffer = &timer_task_tcb;
	*ppxTimerTaskStackBuffer = timer_task_stack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
	void freertos_demo(void){
		//创建开始任务
    StartTask_Handler  = xTaskCreateStatic(	(TaskFunction_t )		start_task,				//任务函数
																						( char * 				)		"start_task",			//任务名字
																						( uint32_t		  )		START_STK_SIZE,		//任务堆栈大小
																						(void *  				)		NULL,							//入口参数
																						(UBaseType_t 		)		START_TASK_PRIO,	//任务优先级
																						(StackType_t * 	)		start_task_stack,	//任务堆栈
																						(StaticTask_t * )		&start_task_tcb );//任务控制块                
    vTaskStartScheduler();          //开启任务调度
}
	
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
      
    //创建task1任务
    Task1_Handler = xTaskCreateStatic((TaskFunction_t )		task1,				//任务函数
																			(char * 				)		"task1",			//任务名字
																			(uint32_t		  	)		TASK1_STK_SIZE,		//任务堆栈大小
																			(void *  				)		NULL,							//入口参数
																			(UBaseType_t 		)		TASK1_PRIO,	//任务优先级
																			(StackType_t * 	)		task1_stack,	//任务堆栈
																			(StaticTask_t * )		&task1_tcb );//任务控制块 
		
    //创建task2任务
    xTaskCreateStatic((TaskFunction_t )		task2,				//任务函数
											(char * 				)		"task2",			//任务名字
											(uint32_t		  	)		TASK2_STK_SIZE,		//任务堆栈大小
											(void *  				)		NULL,							//入口参数
											(UBaseType_t 		)		TASK2_PRIO,	//任务优先级
											(StackType_t * 	)		task2_stack,	//任务堆栈
											(StaticTask_t * )		&task2_tcb );//任务控制块 
								
    //创建task3任务
    xTaskCreateStatic((TaskFunction_t )		task3,				//任务函数
											(char * 				)		"task3",			//任务名字
											(uint32_t		  	)		TASK3_STK_SIZE,		//任务堆栈大小
											(void *  				)		NULL,							//入口参数
											(UBaseType_t 		)		TASK3_PRIO,	//任务优先级
											(StackType_t * 	)		task3_stack,	//任务堆栈
											(StaticTask_t * )		&task3_tcb );//任务控制块 
								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，实现LED1每500ms翻转一次
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	while(1){
		printf("task1正在运行\r\n");
		led_turn(LED1_PORT, LED1_PIN);
		vTaskDelay(500);
	}
}


/**
  * @brief  任务2，实现LED2每500ms翻转一次
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	while(1){
		printf("task2正在运行\r\n");
		led_turn(LED2_PORT, LED2_PIN);
		vTaskDelay(500);
	}
}

/**
  * @brief  判断key1,按下删除task1
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
	while(1){
		printf("task3正在运行\r\n");
		if(key_get_num() == 1){
			if(Task1_Handler != NULL){
				printf("删除task1\r\n");
				vTaskDelete(Task1_Handler); //删除task1
				Task1_Handler = NULL;
			}
			if(Task1_Handler == NULL){
				printf("task1已删除\r\n");
			}
			
		}
		vTaskDelay(10);
	}
}
