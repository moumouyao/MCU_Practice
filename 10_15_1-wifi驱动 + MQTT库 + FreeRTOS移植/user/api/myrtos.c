/*��ʼ���񴴽�3����������1��ʵ��LED1ÿ500ms��תһ��  ����2��ʵ��LED2ÿ500ms��תһ��  ����3���ж�key1,����ɾ��task1*/
#include "myrtos.h"

/**********************��������******************************/

TaskHandle_t StartTask_Handler;           		 //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������
TaskHandle_t Task4_Handler;                    //������
TaskHandle_t Task5_Handler;                    //������
TaskHandle_t Task6_Handler;                    //������
/************************************************************/

/**
  * @brief  FreeRTOS ������ں���
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
        //������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}
    

/**
  * @brief  ��ʼ���������������ڴ�����������
  * @param  None
  * @retval None
  */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
//			LCD_Init();				//LCD����ʼ��
//			kqm_init();				//kqm��ʼ��
//			//su_o3t_init();		//su_o3t��ʼ��
//			dth11_init();			//dth11��ʼ��
//			ADC1_DMA_init();	//ADC1��ͨ��+DMAת�˳�ʼ��
//			sFLASH_Init();
//			esp8266_init();
//			show_index2LCD();
//			Delay_ms(3000);
//			wifi_init();
//			subscription_service();
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

    //����task4����
    xTaskCreate((TaskFunction_t )task4,     
                (const char*    )"task4",   
                (uint16_t       )TASK4_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK4_PRIO,
                (TaskHandle_t*  )&Task4_Handler); 
								
		//����task5����
				xTaskCreate((TaskFunction_t )task5,     
										(const char*    )"task5",   
										(uint16_t       )TASK5_STK_SIZE, 
										(void*          )NULL,
										(UBaseType_t    )TASK5_PRIO,
										(TaskHandle_t*  )&Task5_Handler);
										
		//����task6����
				xTaskCreate((TaskFunction_t )task6,     
										(const char*    )"task6",   
										(uint16_t       )TASK6_STK_SIZE, 
										(void*          )NULL,
										(UBaseType_t    )TASK6_PRIO,
										(TaskHandle_t*  )&Task6_Handler);
								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**
  * @brief  ����1��ʵ��LED1ÿ500ms��תһ��
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("\r\ntask1���гɹ�\r\n");
    while(1){
        
        led_turn(LED1_PORT, LED1_PIN);
			taskENTER_CRITICAL();           //�����ٽ���//
			printf("����\r\n");
			connect_seniverse();
			printf("\r\n��ӡ����\r\n");
			whther_analisys();
			taskEXIT_CRITICAL();            //�˳��ٽ��� 
        vTaskDelay(500);
    }
}


/**
  * @brief  ����2��su_03t����
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
  printf("\r\ntask2���гɹ�\r\n");  
	while(1){
        vioce_analysis();
		
        vTaskDelay(20);
    }
}

/**
  * @brief  �����ϴ��Ʒ�����
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
    while(1){
			taskENTER_CRITICAL();           //�����ٽ���//
			printf("�����ϴ���ʼִ��\r\n");
			send_data2server();
			taskEXIT_CRITICAL();            //�˳��ٽ��� 
				vTaskDelay(1000 * 10);
        }
       
    
}

/**
  * @brief  ����4��lcd��ʾ
  * @param  None
  * @retval None
  */
void task4(void *pvParameters){
    while(1){
        show_time2LCD();
				show_data2LCD();
				//LCD_Clear(LIGHTGREEN);
        vTaskDelay(50);
    }
}

/**
  * @brief  ����5��У׼ʵʱʱ�ӣ���Լÿһ��СʱУ׼һ��
  * @param  None
  * @retval None
  */
void task5(void *pvParameters){
    while(1){
			taskENTER_CRITICAL();           //�����ٽ���
			printf("\r\nУ׼ʵʱʱ��\r\n");
			Time_Adjust();
			taskEXIT_CRITICAL();            //�˳��ٽ���
		vTaskDelay(1000 * 60 * 60);
		
    }
}


/**
  * @brief  ����6�����ִ���������
  * @param  None
  * @retval None
  */
void task6(void *pvParameters){
    while(1){
			taskENTER_CRITICAL();           //�����ٽ���
			printf("��������6\r\n");
			air_analysis();
			
			dht_get_val();
			
			ADC2VOL();
			taskEXIT_CRITICAL();            //�˳��ٽ���
		vTaskDelay(2000);
		
    }
}


