/*��ʼ���񴴽�����1������1��*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;            //������
TaskHandle_t Task1_Handler;                    //������
TaskHandle_t Task2_Handler;                    //������

List_t test_list;	//�����б�
ListItem_t list_item1, list_item2, list_item3;	//�����б���

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
			led_turn(LED1_PORT, LED1_PIN);
			vTaskDelay(500);
				}
        
    
}


/**
  * @brief  ����2���б���Ĳ����ɾ��ʵ��
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	printf("����2��������\r\n");
	vListInitialise(&test_list);	//��ʼ���б�
	vListInitialiseItem(&list_item1);	//��ʼ���б���1
	vListInitialiseItem(&list_item2);	//��ʼ���б���2
	vListInitialiseItem(&list_item3);	//��ʼ���б���3
  //�б�����������ֵ
	list_item1.xItemValue = 40;
	list_item2.xItemValue = 60;
	list_item3.xItemValue = 50;
	//��ӡ�б���б��������Ϣ
	printf("/**************�ڶ�������ӡ�б���б���ĵ�ַ**************/\r\n");
    printf("��Ŀ\t\t\t��ַ\r\n");
    printf("TestList\t\t0x%p\t\r\n", &test_list);
    printf("TestList->pxIndex\t0x%p\t\r\n", test_list.pxIndex);
    printf("TestList->xListEnd\t0x%p\t\r\n", (&test_list.xListEnd));
    printf("ListItem1\t\t0x%p\t\r\n", &list_item1);
    printf("ListItem2\t\t0x%p\t\r\n", &list_item2);
    printf("ListItem3\t\t0x%p\t\r\n", &list_item3);
    printf("/**************************����***************************/\r\n");
    
    printf("\r\n/*****************���������б���1�����б�******************/\r\n");
    vListInsert((List_t*    )&test_list,         /* �б� */
                (ListItem_t*)&list_item1);       /* �б��� */
    printf("��Ŀ\t\t\t\t��ַ\r\n");
    printf("TestList->xListEnd->pxNext\t0x%p\r\n", (test_list.xListEnd.pxNext));
    printf("ListItem1->pxNext\t\t0x%p\r\n", (list_item1.pxNext));
    printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (test_list.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious\t\t0x%p\r\n", (list_item1.pxPrevious));
    printf("/**************************����***************************/\r\n");
		
		printf("\r\n/*****************���Ĳ����б���2�����б�******************/\r\n");
    vListInsert((List_t*    )&test_list,         /* �б� */
                (ListItem_t*)&list_item2);       /* �б��� */
    printf("��Ŀ\t\t\t\t��ַ\r\n");
    printf("TestList->xListEnd->pxNext\t0x%p\r\n", (test_list.xListEnd.pxNext));
    printf("ListItem1->pxNext\t\t0x%p\r\n", (list_item1.pxNext));
		printf("ListItem2->pxNext\t\t0x%p\r\n", (list_item2.pxNext));
    printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (test_list.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious\t\t0x%p\r\n", (list_item1.pxPrevious));
		printf("ListItem2->pxPrevious\t\t0x%p\r\n", (list_item2.pxPrevious));
    printf("/**************************����***************************/\r\n");
		
		printf("\r\n/*****************���岽���б���3�����б�******************/\r\n");
    vListInsert((List_t*    )&test_list,         /* �б� */
                (ListItem_t*)&list_item3);       /* �б��� */
    printf("��Ŀ\t\t\t\t��ַ\r\n");
    printf("TestList->xListEnd->pxNext\t0x%p\r\n", (test_list.xListEnd.pxNext));
    printf("ListItem1->pxNext\t\t0x%p\r\n", (list_item1.pxNext));
		printf("ListItem2->pxNext\t\t0x%p\r\n", (list_item2.pxNext));
		printf("ListItem3->pxNext\t\t0x%p\r\n", (list_item3.pxNext));
    printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (test_list.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious\t\t0x%p\r\n", (list_item1.pxPrevious));
		printf("ListItem2->pxPrevious\t\t0x%p\r\n", (list_item2.pxPrevious));
		printf("ListItem3->pxPrevious\t\t0x%p\r\n", (list_item3.pxPrevious));
    printf("/**************************����***************************/\r\n");
    while(1){
       vTaskDelay(1000);
    }
}





















