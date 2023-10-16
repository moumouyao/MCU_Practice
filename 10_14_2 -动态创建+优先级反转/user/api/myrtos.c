/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄

QueueHandle_t BINARY_SEMAPHORE_handle;				//二值信号量句柄

/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//创建二值信号量
			BINARY_SEMAPHORE_handle = xSemaphoreCreateBinary();
			if(BINARY_SEMAPHORE_handle == NULL){
				printf("二值信号量创建失败\r\n");
			}
			else{
				printf("二值信号量创建成功\r\n");
			}
			xSemaphoreGive(BINARY_SEMAPHORE_handle);
			
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
                (TaskHandle_t*  )&Task2_Handler); 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，低优先级任务
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("任务1正常运行\r\n");
    while(1){
			//led_turn(LED1_PORT, LED1_PIN);
			printf("获取信号量\r\n");
			xSemaphoreTake(BINARY_SEMAPHORE_handle, portMAX_DELAY);
			printf("低优先级任务正在运行\r\n");
				Delay_ms(3000);
			printf("低优先级任务释放信号量\r\n");
			xSemaphoreGive(BINARY_SEMAPHORE_handle);
			
			vTaskDelay(10);
				}
        
    
}


/**
  * @brief  中优先级任务
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	printf("任务2正常运行\r\n");
	while(1){
		printf("中优先级任务正在运行\r\n");
		vTaskDelay(1000);
	}
}

/**
  * @brief  任务3，高优先级任务
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
	printf("任务3正常运行\r\n");
	while(1){
			//led_turn(LED1_PORT, LED1_PIN);
			printf("获取信号量\r\n");
			xSemaphoreTake(BINARY_SEMAPHORE_handle, portMAX_DELAY);
			printf("高优先级任务正在运行\r\n");
				Delay_ms(1000);
			printf("高优先级任务释放信号量\r\n");
			xSemaphoreGive(BINARY_SEMAPHORE_handle);
			
			vTaskDelay(1000);
				}
	while(1){
		
			
	}
}




















