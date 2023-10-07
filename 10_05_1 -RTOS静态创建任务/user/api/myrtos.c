#include "myrtos.h"
/*�������������********************************************************************/

/*��ʼ����*/
TaskHandle_t StartTask_Handler;			//������
StackType_t start_task_stack[START_STK_SIZE];
StaticTask_t start_task_tcb;

/*����1*/
TaskHandle_t Task1_Handler;					//������
StackType_t task1_stack[TASK1_STK_SIZE];
StaticTask_t task1_tcb;

/*����2*/
TaskHandle_t Task2_Handler;					//������
StackType_t task2_stack[TASK2_STK_SIZE];
StaticTask_t task2_tcb;

/*����3*/
TaskHandle_t Task3_Handler;					//������
StackType_t task3_stack[TASK3_STK_SIZE];
StaticTask_t task3_tcb;
/**************************************************************************************/

/**
  * @brief  ��̬���������ڴ����
  * @param  StaticTask_t **ppxIdleTaskTCBBuffer		�������� ������ƿ�
  * @param 	StackType_t **ppxIdleTaskStackBuffer	��������������ջ
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
  * @brief  �����ʱ���ڴ����
  * @param  StaticTask_t **ppxTimerTaskTCBBuffer		�����ʱ��������ƿ� 																
  * @param  StackType_t **ppxTimerTaskStackBuffer		�����ʱ�������ջ 																		 
  * @param  uint32_t *pulTimerTaskStackSize					��ջ��С
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
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
	void freertos_demo(void){
		//������ʼ����
    StartTask_Handler  = xTaskCreateStatic(	(TaskFunction_t )		start_task,				//������
																						( char * 				)		"start_task",			//��������
																						( uint32_t		  )		START_STK_SIZE,		//�����ջ��С
																						(void *  				)		NULL,							//��ڲ���
																						(UBaseType_t 		)		START_TASK_PRIO,	//�������ȼ�
																						(StackType_t * 	)		start_task_stack,	//�����ջ
																						(StaticTask_t * )		&start_task_tcb );//������ƿ�                
    vTaskStartScheduler();          //�����������
}
	
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
      
    //����task1����
    Task1_Handler = xTaskCreateStatic((TaskFunction_t )		task1,				//������
																			(char * 				)		"task1",			//��������
																			(uint32_t		  	)		TASK1_STK_SIZE,		//�����ջ��С
																			(void *  				)		NULL,							//��ڲ���
																			(UBaseType_t 		)		TASK1_PRIO,	//�������ȼ�
																			(StackType_t * 	)		task1_stack,	//�����ջ
																			(StaticTask_t * )		&task1_tcb );//������ƿ� 
		
    //����task2����
    xTaskCreateStatic((TaskFunction_t )		task2,				//������
											(char * 				)		"task2",			//��������
											(uint32_t		  	)		TASK2_STK_SIZE,		//�����ջ��С
											(void *  				)		NULL,							//��ڲ���
											(UBaseType_t 		)		TASK2_PRIO,	//�������ȼ�
											(StackType_t * 	)		task2_stack,	//�����ջ
											(StaticTask_t * )		&task2_tcb );//������ƿ� 
								
    //����task3����
    xTaskCreateStatic((TaskFunction_t )		task3,				//������
											(char * 				)		"task3",			//��������
											(uint32_t		  	)		TASK3_STK_SIZE,		//�����ջ��С
											(void *  				)		NULL,							//��ڲ���
											(UBaseType_t 		)		TASK3_PRIO,	//�������ȼ�
											(StackType_t * 	)		task3_stack,	//�����ջ
											(StaticTask_t * )		&task3_tcb );//������ƿ� 
								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
  * @brief  ����1��ʵ��LED1ÿ500ms��תһ��
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	while(1){
		printf("task1��������\r\n");
		led_turn(LED1_PORT, LED1_PIN);
		vTaskDelay(500);
	}
}


/**
  * @brief  ����2��ʵ��LED2ÿ500ms��תһ��
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	while(1){
		printf("task2��������\r\n");
		led_turn(LED2_PORT, LED2_PIN);
		vTaskDelay(500);
	}
}

/**
  * @brief  �ж�key1,����ɾ��task1
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
	while(1){
		printf("task3��������\r\n");
		if(key_get_num() == 1){
			if(Task1_Handler != NULL){
				printf("ɾ��task1\r\n");
				vTaskDelete(Task1_Handler); //ɾ��task1
				Task1_Handler = NULL;
			}
			if(Task1_Handler == NULL){
				printf("task1��ɾ��\r\n");
			}
			
		}
		vTaskDelay(10);
	}
}
