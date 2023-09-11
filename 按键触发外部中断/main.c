#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "interrupt.h"

//void key_led(void);
void key_led(void);
void key_buzzer(void);

int main(){
	//buuzer_init();
	key_init();
	//key_led();
	//Á÷Ë®µÆ
	key1_interrupt_init();
	key2_interrupt_init();
	while(1){};
	//waterfall_light();
	//	key_buzzer();
	//key_led();
	
}

/**
  * @brief  °´¼ü¿ØÖÆ·äÃùÆ÷
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
  * @brief  °´¼ü¿ØÖÆledµÆ
	*						°´¼ü1 µãÁÁËÄ¸öLEDµÆ
	*						°´¼ü2	ºìµÆÁÁ
	*						°´¼ü3 ÂÌµÆÁÁ
	*						°´¼ü4 À¶µÆÁÁ
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

















