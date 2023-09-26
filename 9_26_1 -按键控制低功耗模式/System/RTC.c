#include "RTC.h"

void rtc_init(void){
	
	//成立表示RTC已经设置过，不需要重复设置
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    printf("RTC not yet configured....\r\n\n");

    /* RTC Configuration */
    RTC_Configuration();

    printf("RTC configured....\r\n");

    /* Adjust time by values entered by the user on the hyperterminal */
    Time_Adjust();

    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
  else
  {
		//检查复位原因
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("Power On Reset occurred....\r\n\n");
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("External Reset occurred....\r\n\n");
    }

    printf("No need to configure RTC....\r\n");
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();	//等待寄存器同步

    /* Enable the RTC Second */
		NVIC_Configuration();
    RTC_ITConfig(RTC_IT_SEC, DISABLE);	//开启秒中断
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
void RTC_Configuration(void)
{
	//使能电源和BKP时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	//使能 RTC 和后备寄存器访问
  PWR_BackupAccessCmd(ENABLE);

	//将外设 BKP 的全部寄存器重设为缺省值
  BKP_DeInit();

	//设置外部低速晶振（LSE）
  RCC_LSEConfig(RCC_LSE_ON);
	//等待LSE准备完成
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

		//设置 RTC 时钟（RTCCLK） 
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	//使能RTC时钟
  RCC_RTCCLKCmd(ENABLE);

		//等待RTC寄存器同步
  RTC_WaitForSynchro();

		//等待上一次写操作完成
  RTC_WaitForLastTask();

		//设置秒中断
  RTC_ITConfig(RTC_IT_SEC, DISABLE);

		//等待上一次操作完成
  RTC_WaitForLastTask();

	//设置时钟分频
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

	//等待上一次操作完成
  RTC_WaitForLastTask();
}

/**
  * @brief  Adjusts time.
  * @param  None
  * @retval None
  */
void Time_Adjust(void)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
	//设置 RTC 计数器的值
  /* Change the current time */
		RTC_SetCounter(Time_Regulate());
	// RTC_SetCounter(0);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}



/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @param  None
  * @retval Current time RTC counter value
  */
uint32_t Time_Regulate(void){
	struct tm current_time = {0, 30, 15, 25, 9 - 1, 2023 - 1900};
	return mktime(&current_time);
}



//串口显示时间
void show_time(void){
	time_t current_sec = 0;
	current_sec = RTC_GetCounter();
	struct tm *time_info = NULL;
	time_info = localtime(&current_sec);
	printf("%d-%d-%d %d:%d:%d\r\n", time_info->tm_year + 1900,
																	time_info->tm_mon + 1, 
																	time_info->tm_mday, 
																	time_info->tm_hour, 
																	time_info->tm_min, 
																	time_info->tm_sec);	
}


