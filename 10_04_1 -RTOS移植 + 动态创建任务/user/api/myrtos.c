/*��ʼ���񴴽�3����������1��ʵ��LED1ÿ500ms��תһ��  ����2��ʵ��LED2ÿ500ms��תһ��  ����3���ж�key1,����ɾ��task1*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;            //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������
TaskHandle_t Task3_Handler;                    //������
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