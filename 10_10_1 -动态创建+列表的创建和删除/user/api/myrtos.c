/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;            //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄

List_t test_list;	//测试列表
ListItem_t list_item1, list_item2, list_item3;	//测试列表项

/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
        //创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}
    
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
      
    //创建task1任务
    xTaskCreate((TaskFunction_t )task1,     
                (const char*    )"task1",   
                (uint16_t       )TASK1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1_Handler); 
    
		//创建task2任务
    xTaskCreate((TaskFunction_t )task2,     
                (const char*    )"task2",   
                (uint16_t       )TASK2_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK2_PRIO,
                (TaskHandle_t*  )&Task2_Handler); 
                                
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
			led_turn(LED1_PORT, LED1_PIN);
			vTaskDelay(500);
				}
        
    
}


/**
  * @brief  任务2，列表项的插入和删除实验
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	printf("任务2正常运行\r\n");
	vListInitialise(&test_list);	//初始化列表
	vListInitialiseItem(&list_item1);	//初始化列表项1
	vListInitialiseItem(&list_item2);	//初始化列表项2
	vListInitialiseItem(&list_item3);	//初始化列表项3
  //列表项排序句柄赋值
	list_item1.xItemValue = 40;
	list_item2.xItemValue = 60;
	list_item3.xItemValue = 50;
	//打印列表和列表项相关信息
	printf("/**************第二步：打印列表和列表项的地址**************/\r\n");
    printf("项目\t\t\t地址\r\n");
    printf("TestList\t\t0x%p\t\r\n", &test_list);
    printf("TestList->pxIndex\t0x%p\t\r\n", test_list.pxIndex);
    printf("TestList->xListEnd\t0x%p\t\r\n", (&test_list.xListEnd));
    printf("ListItem1\t\t0x%p\t\r\n", &list_item1);
    printf("ListItem2\t\t0x%p\t\r\n", &list_item2);
    printf("ListItem3\t\t0x%p\t\r\n", &list_item3);
    printf("/**************************结束***************************/\r\n");
    
    printf("\r\n/*****************第三步：列表项1插入列表******************/\r\n");
    vListInsert((List_t*    )&test_list,         /* 列表 */
                (ListItem_t*)&list_item1);       /* 列表项 */
    printf("项目\t\t\t\t地址\r\n");
    printf("TestList->xListEnd->pxNext\t0x%p\r\n", (test_list.xListEnd.pxNext));
    printf("ListItem1->pxNext\t\t0x%p\r\n", (list_item1.pxNext));
    printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (test_list.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious\t\t0x%p\r\n", (list_item1.pxPrevious));
    printf("/**************************结束***************************/\r\n");
		
		printf("\r\n/*****************第四步：列表项2插入列表******************/\r\n");
    vListInsert((List_t*    )&test_list,         /* 列表 */
                (ListItem_t*)&list_item2);       /* 列表项 */
    printf("项目\t\t\t\t地址\r\n");
    printf("TestList->xListEnd->pxNext\t0x%p\r\n", (test_list.xListEnd.pxNext));
    printf("ListItem1->pxNext\t\t0x%p\r\n", (list_item1.pxNext));
		printf("ListItem2->pxNext\t\t0x%p\r\n", (list_item2.pxNext));
    printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (test_list.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious\t\t0x%p\r\n", (list_item1.pxPrevious));
		printf("ListItem2->pxPrevious\t\t0x%p\r\n", (list_item2.pxPrevious));
    printf("/**************************结束***************************/\r\n");
		
		printf("\r\n/*****************第五步：列表项3插入列表******************/\r\n");
    vListInsert((List_t*    )&test_list,         /* 列表 */
                (ListItem_t*)&list_item3);       /* 列表项 */
    printf("项目\t\t\t\t地址\r\n");
    printf("TestList->xListEnd->pxNext\t0x%p\r\n", (test_list.xListEnd.pxNext));
    printf("ListItem1->pxNext\t\t0x%p\r\n", (list_item1.pxNext));
		printf("ListItem2->pxNext\t\t0x%p\r\n", (list_item2.pxNext));
		printf("ListItem3->pxNext\t\t0x%p\r\n", (list_item3.pxNext));
    printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (test_list.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious\t\t0x%p\r\n", (list_item1.pxPrevious));
		printf("ListItem2->pxPrevious\t\t0x%p\r\n", (list_item2.pxPrevious));
		printf("ListItem3->pxPrevious\t\t0x%p\r\n", (list_item3.pxPrevious));
    printf("/**************************结束***************************/\r\n");
    while(1){
       vTaskDelay(1000);
    }
}





















