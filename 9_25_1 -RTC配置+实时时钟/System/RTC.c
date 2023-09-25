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
    RTC_ITConfig(RTC_IT_SEC, ENABLE);	//开启秒中断
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
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	//使能或者失能 RTC 和后备寄存器访问
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

	//将外设 BKP 的全部寄存器重设为缺省值
  /* Reset Backup Domain */
  BKP_DeInit();

	//设置外部低速晶振（LSE）
  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
	//等待LSE准备完成
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

		//设置 RTC 时钟（RTCCLK） 
  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

		//等待RTC寄存器同步
  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

		//等待上一次写操作完成
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

		//设置秒中断
  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

		//等待上一次操作完成
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

	//设置时钟分频
  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

	//等待上一次操作完成
  /* Wait until last write operation on RTC registers has finished */
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

