#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "exti.h"

//void key_led(void);
void key_led(void);
void key_buzzer(void);
void exit_key1(void);
void exit_key2(void);
void exit_key3(void);
void exit_key4(void);
void waterfall_light_exit(void);

int main(){
	RGB_init();
	key_init();
	buzzer_init();
	key1_exit_init();
	key2_exit_init();
	key3_exit_init();
	key4_exit_init();
	led_init(LED1);
	waterfall_light_exit();
	while(1){
		
		exit_key1();
		exit_key2();
		exit_key3();
		exit_key4();
	}
}

void waterfall_light_exit(void){
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);
	led_init(LED4);
	while(1){
		led_enable(LED1);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(200);
		led_disable(LED1);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(20);
		led_enable(LED2);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(200);
		led_disable(LED2);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(20);
		led_enable(LED3);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(200);
		led_disable(LED3);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(20);
		led_enable(LED4);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(200);
		led_disable(LED4);exit_key1();exit_key2();exit_key3();exit_key4();
		Delay_ms(20);
	}
}

/**
  * @brief  按键1通过中断控制蜂鸣器
  * @param  None
  * @retval None
  */
void exit_key1(void){
	if(get_key_val(KEY1) == 1){
		buzzer_enable();
	}
	else{
		buzzer_disable();
	}
}

/**
  * @brief  按键2通过中断RGB红灯
  * @param  None
  * @retval None
  */
void exit_key2(void){
	if(get_key_val(KEY2) == 1){
			RGB_enable(RED); 
	}
	else{
			RGB_disable(RED);
				}
}

/**
  * @brief  按键3通过中断RGB绿灯
  * @param  None
  * @retval None
  */
void exit_key3(void){
	if(get_key_val(KEY3) == 1){
			RGB_enable(GREEN); 
	}
	else{
			RGB_disable(GREEN);
				}
}

/**
  * @brief  按键4通过中断RGB蓝灯
  * @param  None
  * @retval None
  */
void exit_key4(void){
	if(get_key_val(KEY4) == 1){
			RGB_enable(BLUE); 
	}
	else{
			RGB_disable(BLUE);
				}
}


/**
  * @brief  按键控制蜂鸣器
  * @param  None
  * @retval None
  */
void key_buzzer(void){
	uint8_t k1 = 0, key_val = 0;
	led_init(LED1);
	buzzer_init();
	key_init();
	while(1){
		key_val = key_get_num();
		if(key_val == 1){
			if(k1 == 0){
					buzzer_enable();
					led_enable(LED1); 
					k1++; 
				}
				else{
					led_disable(LED1);
					buzzer_disable();
					k1 = 0;
				}
	}
		}
}
/**
  * @brief  按键控制led灯
	*						按键1 点亮四个LED灯
	*						按键2	红灯亮
	*						按键3 绿灯亮
	*						按键4 蓝灯亮
  * @param  None
  * @retval None
  */
void key_led(void){
	uint8_t k1 = 0, k2 = 0, k3 = 0, k4 = 0;
	key_init();
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);
	led_init(LED4);
	RGB_init();
	while(1){
		uint8_t keynum = key_get_num();
		switch(keynum){
			case 1:	{
				if(k1 == 0){
					led_enable(LED1); 
					led_enable(LED2); 
					led_enable(LED3); 
					led_enable(LED4); 
					k1++; 
				}
				else{
					led_disable(LED1);
					led_disable(LED2);
					led_disable(LED3);
					led_disable(LED4);
					k1 = 0;
				}
				break;
			}
			case 2:	{
				if(k2 == 0){
					RGB_enable(RED);
					k2++; 
				}
				else{
					RGB_disable(RED);
					k2 = 0;
				}
				break;
			}
			case 3:	{
				if(k3 == 0){
					RGB_enable(GREEN); 
					k3++; 
				}
				else{
					RGB_disable(GREEN);
					k3 = 0;
				}
				break;
			}
			case 4:	{
				if(k4 == 0){
					RGB_enable(BLUE);
					k4++; 
				}
				else{
					RGB_disable(BLUE);
					k4 = 0;
				}
				break;
			}
			default:break;
		}
	}
}

















