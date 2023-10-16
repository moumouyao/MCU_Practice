/*��ʼ���񴴽�����1������1��*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������

QueueHandle_t BINARY_SEMAPHORE_handle;				//��ֵ�ź������

/**
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//������ֵ�ź���
			BINARY_SEMAPHORE_handle = xSemaphoreCreateBinary();
			if(BINARY_SEMAPHORE_handle == NULL){
				printf("��ֵ�ź�������ʧ��\r\n");
			}
			else{
				printf("��ֵ�ź��������ɹ�\r\n");
			}
			xSemaphoreGive(BINARY_SEMAPHORE_handle);
			
        //������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}
    
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
      
    //����task1����
    xTaskCreate((TaskFunction_t )task1,     
                (const char*    )"task1",   
                (uint16_t       )TASK1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1_Handler); 
    
		//����task2����
    xTaskCreate((TaskFunction_t )task2,     
                (const char*    )"task2",   
                (uint16_t       )TASK2_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK2_PRIO,
                (TaskHandle_t*  )&Task2_Handler); 
								
		//����task3����
    xTaskCreate((TaskFunction_t )task3,     
                (const char*    )"task3",   
                (uint16_t       )TASK3_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK3_PRIO,
                (TaskHandle_t*  )&Task2_Handler); 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
  * @brief  ����1�������ȼ�����
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("����1��������\r\n");
    while(1){
			//led_turn(LED1_PORT, LED1_PIN);
			printf("��ȡ�ź���\r\n");
			xSemaphoreTake(BINARY_SEMAPHORE_handle, portMAX_DELAY);
			printf("�����ȼ�������������\r\n");
				Delay_ms(3000);
			printf("�����ȼ������ͷ��ź���\r\n");
			xSemaphoreGive(BINARY_SEMAPHORE_handle);
			
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  �����ȼ�����
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	printf("����2��������\r\n");
	while(1){
		printf("�����ȼ�������������\r\n");
		vTaskDelay(1000);
	}
}

/**
  * @brief  ����3�������ȼ�����
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
	printf("����3��������\r\n");
	while(1){
			//led_turn(LED1_PORT, LED1_PIN);
			printf("��ȡ�ź���\r\n");
			xSemaphoreTake(BINARY_SEMAPHORE_handle, portMAX_DELAY);
			printf("�����ȼ�������������\r\n");
				Delay_ms(1000);
			printf("�����ȼ������ͷ��ź���\r\n");
			xSemaphoreGive(BINARY_SEMAPHORE_handle);
			
			vTaskDelay(1000);
				}
	while(1){
		
			
	}
}




















