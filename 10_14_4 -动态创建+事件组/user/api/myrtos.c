/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;           		 //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄

EventGroupHandle_t event_group_handle;				//事件组句柄

#define	event_bit0	(1 << 0)
#define	event_bit1	(1 << 1)

/**
  * @brief  FreeRTOS 例程入口函数
  * @param  None
  * @retval None
  */
    void freertos_demo(void){
				//创建事件组
			event_group_handle = xEventGroupCreate();
			if(event_group_handle == NULL){
				printf("事件组创建失败\r\n");
			}
			else{
				printf("事件组创建成功\r\n");
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
  * @brief  任务1，key1按下事件组0位置一，key2按下事件组1位置1
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("任务1正常运行\r\n");
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
  * @brief  获取二值信号量
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
	uint8_t key_val = 0;
	EventBits_t err;
	printf("任务2正常运行\r\n");

	while(1){
		 err = xEventGroupWaitBits( (EventGroupHandle_t	)  	event_group_handle,				/* 事件标志组句柄 */
																(EventBits_t   			)		event_bit0 | event_bit1,  /* 等待事件标志组的bit0和bit1位 */
																(BaseType_t   			)		pdTRUE,                   /* 成功等待到事件标志位后，清除事件标志组中的bit0和bit1位 */
																(BaseType_t   			)		pdTRUE,                  /* 等待事件标志组的bit0和bit1位都置1,就成立 */                        
																(TickType_t   			)		portMAX_DELAY);           /* 死等 */
			
		printf("事件组触发成功，数据：%#x\r\n", err);
			
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




















