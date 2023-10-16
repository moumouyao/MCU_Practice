/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄

QueueHandle_t COUNTER_SEMAPHORE_handle;				//计数型信号量句柄

/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//创建计数型信号量
			COUNTER_SEMAPHORE_handle = xSemaphoreCreateCounting(100, 100);
			if(COUNTER_SEMAPHORE_handle == NULL){
				printf("计数型信号量创建失败\r\n");
			}
			else{
				printf("计数型信号量创建成功\r\n");
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
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，key1按下释放计数型信号量
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
			if(key_val == 1){	//释放信号量
				err = xSemaphoreGive(COUNTER_SEMAPHORE_handle);
				if(err == pdPASS){
					printf("释放信号量成功\r\n");
				}
				else{
					printf("释放信号量失败\r\n");
				}
			}
			
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  获取计数型信号量
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	BaseType_t err;
	printf("任务2正常运行\r\n");

	while(1){
		err = xSemaphoreTake(COUNTER_SEMAPHORE_handle, portMAX_DELAY);
			if(err != pdTRUE){
				printf("获取信号量失败\r\n");
			}
			else{
				printf("获取信号量成功，数据：%d\r\n", (int)uxSemaphoreGetCount(COUNTER_SEMAPHORE_handle));
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




















