/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄

QueueHandle_t key_queue;											//键值队列句柄
QueueHandle_t	BINARY_SEMAPHORE_handle;				//二值信号量句柄
QueueSetHandle_t	queue_set_handle;						//队列集句柄

char big_data[128] = "我是一个大数组，很大的数组";	//大数据
//char big_data[128] = "hello world";	//大数据


/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
			
			//创建队列集
			queue_set_handle = xQueueCreateSet(2);
			if(queue_set_handle == NULL){
				printf("队列集创建失败\r\n");
			}
			else{
				printf("队列集创建成功\r\n");
			}
			
				//创建消息队列
			key_queue	= xQueueCreate(1, sizeof(uint8_t));
			if(key_queue == NULL){
				printf("消息队列创建失败\r\n");
			}
			else{
				printf("消息队列创建成功\r\n");
			}
			
			//创建二值信号量
			BINARY_SEMAPHORE_handle = xSemaphoreCreateBinary();
			if(BINARY_SEMAPHORE_handle == NULL){
				printf("二值信号量创建失败\r\n");
			}
			else{
				printf("二值信号量创建成功\r\n");
			}
			
			//添加入队列集
			if(xQueueAddToSet(key_queue, queue_set_handle) == pdFAIL){
				printf("队列集添加成员失败\r\n");
			}
			if(xQueueAddToSet(BINARY_SEMAPHORE_handle, queue_set_handle) == pdFAIL){
				printf("队列集添加成员失败\r\n");
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
//    xTaskCreate((TaskFunction_t )task3,     
//                (const char*    )"task3",   
//                (uint16_t       )TASK3_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )TASK3_PRIO,
//                (TaskHandle_t*  )&Task3_Handler); 
//                                
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，key1按下，向键值队列中写入键值，key2按下释放二值信号量
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("任务1正常运行\r\n");
	uint8_t key_val = 0;
	BaseType_t err;
    while(1){
			led_turn(LED1_PORT, LED1_PIN);
			key_val = key_get_num();
			switch(key_val){
				case 1:
					err = xQueueSend(key_queue, &key_val, portMAX_DELAY); 
						if(err == pdPASS)
							printf("消息队列写入成功\r\n");
						else
							printf("消息队列写入失败\r\n");
							printf("键值 %d\r\n", key_val);
					break;
				case 2:
					err = xSemaphoreGive(BINARY_SEMAPHORE_handle);
				if(err == pdPASS)
							printf("二值信号量释放成功\r\n");
						else
							printf("二值信号量释放失败\r\n");
							printf("键值 %d\r\n", key_val);
					break;
					
			}
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  获取队列集消息	
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	uint8_t key_val = 0;
	BaseType_t err;
	QueueSetMemberHandle_t member_handle;
	printf("任务2正常运行\r\n");

	while(1){
		member_handle = xQueueSelectFromSet(queue_set_handle, portMAX_DELAY);
		if(member_handle == key_queue){
		err = xQueueReceive(key_queue, &key_val, portMAX_DELAY);
			if(err != pdTRUE){
				printf("key_queue出队失败\r\n");
			}
			else{
				printf("key_queue出队成功，数据：%d\r\n", key_val);
			}
		}
		else if(member_handle == BINARY_SEMAPHORE_handle){
		err = xSemaphoreTake(BINARY_SEMAPHORE_handle, portMAX_DELAY);
			if(err != pdTRUE){
				printf("获取二值信号量失败\r\n");
			}
			else{
				printf("获取二值信号成功");
			}
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

	while(1){
	
	}
}




















