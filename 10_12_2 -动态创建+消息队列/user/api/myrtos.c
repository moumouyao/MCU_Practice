/*��ʼ���񴴽�����1������1��*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������

QueueHandle_t key_queue;											//��ֵ���о��
QueueHandle_t	big_data_queue;									//�����ݶ��о��

char big_data[128] = "����һ�������飬�ܴ������";	//������
//char big_data[128] = "hello world";	//������


/**
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//������Ϣ����
			key_queue	= xQueueCreate(2, sizeof(uint8_t));
			if(key_queue == NULL){
				printf("key_queue�������ʧ��\r\n");
			}
			else{
				printf("key_queue��������ɹ�\r\n");
			}
			big_data_queue = xQueueCreate(1, sizeof(char *));
			if(big_data_queue == NULL){
				printf("big_data_queue�������ʧ��\r\n");
			}
			else{
				printf("big_data_queue��������ɹ�\r\n");
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
    xTaskCreate((TaskFunction_t )task3,     
                (const char*    )"task3",   
                (uint16_t       )TASK3_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK3_PRIO,
                (TaskHandle_t*  )&Task3_Handler); 
                                
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
  * @brief  ����1��key1��key2���£����ֵ������д���ֵ��key3����������ݶ�����д�����������ĵ�ַ
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("����1��������\r\n");
	uint8_t key_val = 0;
	BaseType_t err;
	char * pstr  = &big_data[0];
    while(1){
			led_turn(LED1_PORT, LED1_PIN);
			key_val = key_get_num();
			switch(key_val){
				case 1:
				case 2:
					err = xQueueSend(key_queue, &key_val, portMAX_DELAY); 
						if(err == pdTRUE)
							printf("key_queueд��ɹ�\r\n");
						else
							printf("key_queueд��ʧ��\r\n");
							printf("��ֵ %d\r\n", key_val);
					break;
				case 3:
					err = xQueueSend(big_data_queue, &pstr, portMAX_DELAY); 
						if(err == pdTRUE)
							printf("big_data_queueд��ɹ�\r\n");
						else
							printf("big_data_queueд��ʧ��\r\n");
							printf("��ֵ %d\r\n", key_val);
					break;
			}
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  key_queue����
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	uint8_t key_val = 0;
	BaseType_t err;
	printf("����2��������\r\n");

	while(1){
		err = xQueueReceive(key_queue, &key_val, portMAX_DELAY);
			if(err != pdTRUE){
				printf("key_queue����ʧ��\r\n");
			}
			else{
				printf("key_queue���ӳɹ������ݣ�%d\r\n", key_val);
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
	char *str = NULL;
	BaseType_t err;
	while(1){
		err = xQueueReceive(big_data_queue, &str, portMAX_DELAY);
			if(err != pdTRUE){
				printf("big_data_queue����ʧ��\r\n");
			}
			else{
				printf("big_data_queue���ӳɹ������ݣ�%s\r\n", str);
			}
	}
}




















