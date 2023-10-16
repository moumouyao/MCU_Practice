/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄

QueueHandle_t key_queue;											//键值队列句柄
QueueHandle_t	big_data_queue;									//大数据队列句柄

char big_data[128] = "我是一个大数组，很大的数组";	//大数据
//char big_data[128] = "hello world";	//大数据


/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//创建消息队列
			key_queue	= xQueueCreate(2, sizeof(uint8_t));
			if(key_queue == NULL){
				printf("key_queue句柄创建失败\r\n");
			}
			else{
				printf("key_queue句柄创建成功\r\n");
			}
			big_data_queue = xQueueCreate(1, sizeof(char *));
			if(big_data_queue == NULL){
				printf("big_data_queue句柄创建失败\r\n");
			}
			else{
				printf("big_data_queue句柄创建成功\r\n");
			}
			
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
		//创建task3任务
    xTaskCreate((TaskFunction_t )task3,     
                (const char*    )"task3",   
                (uint16_t       )TASK3_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK3_PRIO,
                (TaskHandle_t*  )&Task3_Handler); 
                                
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，key1和key2按下，向键值队列中写入键值，key3按下向大数据队列中写入大数据数组的地址
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("任务1正常运行\r\n");
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
							printf("key_queue写入成功\r\n");
						else
							printf("key_queue写入失败\r\n");
							printf("键值 %d\r\n", key_val);
					break;
				case 3:
					err = xQueueSend(big_data_queue, &pstr, portMAX_DELAY); 
						if(err == pdTRUE)
							printf("big_data_queue写入成功\r\n");
						else
							printf("big_data_queue写入失败\r\n");
							printf("键值 %d\r\n", key_val);
					break;
			}
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  key_queue出队
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	uint8_t key_val = 0;
	BaseType_t err;
	printf("任务2正常运行\r\n");

	while(1){
		err = xQueueReceive(key_queue, &key_val, portMAX_DELAY);
			if(err != pdTRUE){
				printf("key_queue出队失败\r\n");
			}
			else{
				printf("key_queue出队成功，数据：%d\r\n", key_val);
			}
	}
}

/**
  * @brief  任务3，列表项的插入和删除实验
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
	printf("任务3正常运行\r\n");
	char *str = NULL;
	BaseType_t err;
	while(1){
		err = xQueueReceive(big_data_queue, &str, portMAX_DELAY);
			if(err != pdTRUE){
				printf("big_data_queue出队失败\r\n");
			}
			else{
				printf("big_data_queue出队成功，数据：%s\r\n", str);
			}
	}
}




















