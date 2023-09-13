#include "Delay.h"

uint32_t led_tick[2] = {0, 500}, key_tick[2] = {0, 20};
uint32_t  d_ms[2] = {0, 0}, d_us[2] = {0, 0}, d_s[2] = {0, 0};

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	d_us[1] = xus;
	d_us[0] = 0;
	while(d_us[0] < d_us[1]);
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	d_ms[0] = 0;
	d_ms[1] = xms;
	while(d_ms[0] < d_ms[1]);
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	d_s[0] = 0;
	d_s[1] = xs  * 1000 * 1000;
	while(d_s[0] < d_s[1]);
} 

/**
  * @brief  配置系统定时器
	*						每1us产生一次中断
  * @param  None
  * @retval None
  */
void sys_tick_init(void){
	SysTick_Config(72000000 / 1000000);	//系统定时器1us产生一次中断
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	led_tick[0]++;
	key_tick[0]++;
	d_ms[0]++;
	d_us[0]++;
	d_s[0]++;
}
