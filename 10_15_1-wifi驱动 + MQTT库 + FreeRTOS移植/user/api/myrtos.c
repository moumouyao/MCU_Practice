/*开始任务创建3个任务，任务1，实现LED1每500ms翻转一次  任务2，实现LED2每500ms翻转一次  任务3，判断key1,按下删除task1*/
#include "myrtos.h"

/**********************任务配置******************************/

TaskHandle_t StartTask_Handler;           		 //任务句柄
TaskHandle_t Task1_Handler;                    //任务句柄
TaskHandle_t Task2_Handler;                    //任务句柄
TaskHandle_t Task3_Handler;                    //任务句柄
TaskHandle_t Task4_Handler;                    //任务句柄
TaskHandle_t Task5_Handler;                    //任务句柄
TaskHandle_t Task6_Handler;                    //任务句柄
/************************************************************/

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
    

/**
  * @brief  开始任务任务函数，用于创建其他任务
  * @param  None
  * @retval None
  */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
//			LCD_Init();				//LCD屏初始化
//			kqm_init();				//kqm初始化
//			//su_o3t_init();		//su_o3t初始化
//			dth11_init();			//dth11初始化
//			ADC1_DMA_init();	//ADC1多通道+DMA转运初始化
//			sFLASH_Init();
//			esp8266_init();
//			show_index2LCD();
//			Delay_ms(3000);
//			wifi_init();
//			subscription_service();
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

    //创建task4任务
    xTaskCreate((TaskFunction_t )task4,     
                (const char*    )"task4",   
                (uint16_t       )TASK4_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK4_PRIO,
                (TaskHandle_t*  )&Task4_Handler); 
								
		//创建task5任务
				xTaskCreate((TaskFunction_t )task5,     
										(const char*    )"task5",   
										(uint16_t       )TASK5_STK_SIZE, 
										(void*          )NULL,
										(UBaseType_t    )TASK5_PRIO,
										(TaskHandle_t*  )&Task5_Handler);
										
		//创建task6任务
				xTaskCreate((TaskFunction_t )task6,     
										(const char*    )"task6",   
										(uint16_t       )TASK6_STK_SIZE, 
										(void*          )NULL,
										(UBaseType_t    )TASK6_PRIO,
										(TaskHandle_t*  )&Task6_Handler);
								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

/**
  * @brief  任务1，实现LED1每500ms翻转一次
  * @param  None
  * @retval None
  */
void task1(void *pvParameters){
	printf("\r\ntask1运行成功\r\n");
    while(1){
        
        led_turn(LED1_PORT, LED1_PIN);
			taskENTER_CRITICAL();           //进入临界区//
			printf("天气\r\n");
			connect_seniverse();
			printf("\r\n打印数据\r\n");
			whther_analisys();
			taskEXIT_CRITICAL();            //退出临界区 
        vTaskDelay(500);
    }
}


/**
  * @brief  任务2，su_03t控制
  * @param  None
  * @retval None
  */
void task2(void *pvParameters){
  printf("\r\ntask2运行成功\r\n");  
	while(1){
        vioce_analysis();
		
        vTaskDelay(20);
    }
}

/**
  * @brief  数据上传云服务器
  * @param  None
  * @retval None
  */
void task3(void *pvParameters){
    while(1){
			taskENTER_CRITICAL();           //进入临界区//
			printf("数据上传开始执行\r\n");
			send_data2server();
			taskEXIT_CRITICAL();            //退出临界区 
				vTaskDelay(1000 * 10);
        }
       
    
}

/**
  * @brief  任务4，lcd显示
  * @param  None
  * @retval None
  */
void task4(void *pvParameters){
    while(1){
        show_time2LCD();
				show_data2LCD();
				//LCD_Clear(LIGHTGREEN);
        vTaskDelay(50);
    }
}

/**
  * @brief  任务5，校准实时时钟，大约每一个小时校准一次
  * @param  None
  * @retval None
  */
void task5(void *pvParameters){
    while(1){
			taskENTER_CRITICAL();           //进入临界区
			printf("\r\n校准实时时钟\r\n");
			Time_Adjust();
			taskEXIT_CRITICAL();            //退出临界区
		vTaskDelay(1000 * 60 * 60);
		
    }
}


/**
  * @brief  任务6，各种传感器采样
  * @param  None
  * @retval None
  */
void task6(void *pvParameters){
    while(1){
			taskENTER_CRITICAL();           //进入临界区
			printf("进入任务6\r\n");
			air_analysis();
			
			dht_get_val();
			
			ADC2VOL();
			taskEXIT_CRITICAL();            //退出临界区
		vTaskDelay(2000);
		
    }
}


