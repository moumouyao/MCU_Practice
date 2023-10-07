/*开始任务创建任务1，任务1，*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;            //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄

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
        
                                
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，实现LED1每500ms翻转一次
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	uint8_t task1_num = 0;
    while(1){
        if(++task1_num == 5){
					task1_num = 0;
					printf("关中断\r\n");
					portDISABLE_INTERRUPTS();
					Delay_ms(5000);
					printf("开中断\r\n");
					portENABLE_INTERRUPTS();
				}
        vTaskDelay(1000);
    }
}


