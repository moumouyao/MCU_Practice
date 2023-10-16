/*��ʼ���񴴽�����1������1��*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������

QueueHandle_t key_queue;											//��ֵ���о��
QueueHandle_t	BINARY_SEMAPHORE_handle;				//��ֵ�ź������
QueueSetHandle_t	queue_set_handle;						//���м����

char big_data[128] = "����һ�������飬�ܴ������";	//������
//char big_data[128] = "hello world";	//������


/**
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
			
			//�������м�
			queue_set_handle = xQueueCreateSet(2);
			if(queue_set_handle == NULL){
				printf("���м�����ʧ��\r\n");
			}
			else{
				printf("���м������ɹ�\r\n");
			}
			
				//������Ϣ����
			key_queue	= xQueueCreate(1, sizeof(uint8_t));
			if(key_queue == NULL){
				printf("��Ϣ���д���ʧ��\r\n");
			}
			else{
				printf("��Ϣ���д����ɹ�\r\n");
			}
			
			//������ֵ�ź���
			BINARY_SEMAPHORE_handle = xSemaphoreCreateBinary();
			if(BINARY_SEMAPHORE_handle == NULL){
				printf("��ֵ�ź�������ʧ��\r\n");
			}
			else{
				printf("��ֵ�ź��������ɹ�\r\n");
			}
			
			//�������м�
			if(xQueueAddToSet(key_queue, queue_set_handle) == pdFAIL){
				printf("���м���ӳ�Աʧ��\r\n");
			}
			if(xQueueAddToSet(BINARY_SEMAPHORE_handle, queue_set_handle) == pdFAIL){
				printf("���м���ӳ�Աʧ��\r\n");
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
		//����task3����
//    xTaskCreate((TaskFunction_t )task3,     
//                (const char*    )"task3",   
//                (uint16_t       )TASK3_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )TASK3_PRIO,
//                (TaskHandle_t*  )&Task3_Handler); 
//                                
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
  * @brief  ����1��key1���£����ֵ������д���ֵ��key2�����ͷŶ�ֵ�ź���
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
			switch(key_val){
				case 1:
					err = xQueueSend(key_queue, &key_val, portMAX_DELAY); 
						if(err == pdPASS)
							printf("��Ϣ����д��ɹ�\r\n");
						else
							printf("��Ϣ����д��ʧ��\r\n");
							printf("��ֵ %d\r\n", key_val);
					break;
				case 2:
					err = xSemaphoreGive(BINARY_SEMAPHORE_handle);
				if(err == pdPASS)
							printf("��ֵ�ź����ͷųɹ�\r\n");
						else
							printf("��ֵ�ź����ͷ�ʧ��\r\n");
							printf("��ֵ %d\r\n", key_val);
					break;
					
			}
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  ��ȡ���м���Ϣ	
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	uint8_t key_val = 0;
	BaseType_t err;
	QueueSetMemberHandle_t member_handle;
	printf("����2��������\r\n");

	while(1){
		member_handle = xQueueSelectFromSet(queue_set_handle, portMAX_DELAY);
		if(member_handle == key_queue){
		err = xQueueReceive(key_queue, &key_val, portMAX_DELAY);
			if(err != pdTRUE){
				printf("key_queue����ʧ��\r\n");
			}
			else{
				printf("key_queue���ӳɹ������ݣ�%d\r\n", key_val);
			}
		}
		else if(member_handle == BINARY_SEMAPHORE_handle){
		err = xSemaphoreTake(BINARY_SEMAPHORE_handle, portMAX_DELAY);
			if(err != pdTRUE){
				printf("��ȡ��ֵ�ź���ʧ��\r\n");
			}
			else{
				printf("��ȡ��ֵ�źųɹ�");
			}
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




















