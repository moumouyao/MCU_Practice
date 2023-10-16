/*��ʼ���񴴽�����1������1��*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������

EventGroupHandle_t event_group_handle;				//�¼�����

#define	event_bit0	(1 << 0)
#define	event_bit1	(1 << 1)

/**
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//�����¼���
			event_group_handle = xEventGroupCreate();
			if(event_group_handle == NULL){
				printf("�¼��鴴��ʧ��\r\n");
			}
			else{
				printf("�¼��鴴���ɹ�\r\n");
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
  * @brief  ����1��key1�����¼���0λ��һ��key2�����¼���1λ��1
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("����1��������\r\n");
	uint8_t key_val = 0;
	EventBits_t err;
    while(1){
			led_turn(LED1_PORT, LED1_PIN);
			key_val = key_get_num();
			if(key_val == 1){	
				xEventGroupSetBits(event_group_handle, event_bit0);
			}
			else if(key_val == 2){	
				xEventGroupSetBits(event_group_handle, event_bit1);
			}
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  ��ȡ��ֵ�ź���
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	uint8_t key_val = 0;
	EventBits_t err;
	printf("����2��������\r\n");

	while(1){
		 err = xEventGroupWaitBits( (EventGroupHandle_t	)  	event_group_handle,				/* �¼���־���� */
																(EventBits_t   			)		event_bit0 | event_bit1,  /* �ȴ��¼���־���bit0��bit1λ */
																(BaseType_t   			)		pdTRUE,                   /* �ɹ��ȴ����¼���־λ������¼���־���е�bit0��bit1λ */
																(BaseType_t   			)		pdTRUE,                  /* �ȴ��¼���־���bit0��bit1λ����1,�ͳ��� */                        
																(TickType_t   			)		portMAX_DELAY);           /* ���� */
			
		printf("�¼��鴥���ɹ������ݣ�%#x\r\n", err);
			
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




















