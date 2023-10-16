/*��ʼ���񴴽�����1������1��*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������

QueueHandle_t COUNTER_SEMAPHORE_handle;				//�������ź������

/**
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//�����������ź���
			COUNTER_SEMAPHORE_handle = xSemaphoreCreateCounting(100, 100);
			if(COUNTER_SEMAPHORE_handle == NULL){
				printf("�������ź�������ʧ��\r\n");
			}
			else{
				printf("�������ź��������ɹ�\r\n");
			}

			
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
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
  * @brief  ����1��key1�����ͷż������ź���
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("����1��������\r\n");
	uint8_t key_val = 0;
	BaseType_t err;
    while(1){
			led_turn(LED1_PORT, LED1_PIN);
			key_val = key_get_num();
			if(key_val == 1){	//�ͷ��ź���
				err = xSemaphoreGive(COUNTER_SEMAPHORE_handle);
				if(err == pdPASS){
					printf("�ͷ��ź����ɹ�\r\n");
				}
				else{
					printf("�ͷ��ź���ʧ��\r\n");
				}
			}
			
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  ��ȡ�������ź���
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	BaseType_t err;
	printf("����2��������\r\n");

	while(1){
		err = xSemaphoreTake(COUNTER_SEMAPHORE_handle, portMAX_DELAY);
			if(err != pdTRUE){
				printf("��ȡ�ź���ʧ��\r\n");
			}
			else{
				printf("��ȡ�ź����ɹ������ݣ�%d\r\n", (int)uxSemaphoreGetCount(COUNTER_SEMAPHORE_handle));
			}
	}
}

/**
  * @brief  ����3���б���Ĳ����ɾ��ʵ��
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
	printf("����3��������\r\n");
	while(1){
		
			
	}
}




















