/*开始任务创建3个任务，任务1，实现LED1每500ms翻转一次  任务2，实现LED2每500ms翻转一次  任务3，判断key1,按下删除task1*/
#include "myrtos.h"

TaskHandle_t StartTask_Handler;            //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄
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
  * @brief  任务1，实现LED1每500ms翻转一次
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
    while(1){
        printf("task1正在运行\r\n");
        led_turn(LED1_PORT, LED1_PIN);
        vTaskDelay(500);
    }
}


/**
  * @brief  任务2，实现LED2每500ms翻转一次
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
    while(1){
        printf("task2正在运行\r\n");
        led_turn(LED2_PORT, LED2_PIN);
        vTaskDelay(500);
    }
}

/**
  * @brief  key1按下挂起task1，key2按下恢复task1，key3按下在中断中恢复task1
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
    while(1){
			uint8_t key = key_get_num();
        if(key == 1){
					printf("task1已经挂起\r\n");
           vTaskSuspend(Task1_Handler);
            }
				if(key == 2){
					printf("task1恢复运行\r\n");
					vTaskResume(Task1_Handler);
				}
//				else if(key_get_num() == 3){
//					vTaskResume(Task1_Handler);
//				}
           
				vTaskDelay(10);
        }
       
    
}