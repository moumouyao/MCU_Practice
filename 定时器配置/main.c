#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "interrupt.h"
#include "timer.h"



//void key_led(void);
void key_led(void);
void water_led(void);
uint8_t num = 0;
int main(){
	RGB_init();
	led_init(LED1);
	led_init(LED2);
	buzzer_init();
	sys_tick_init();
	while(1){
		led_enable(LED1);
		//if(led_tick[0] > led_tick[1]){
		//buzzer_turn(BUZZER_PORT, BUZZER_PIN);
		led_turn(LED2_PORT,LED2_PIN);
		Delay_s(1);
			//led_tick[0] = 0;
	//}
		
			
	}
}

/**
  * @brief  ��������led��
	*						����4�������� 
	*						����1	���
	*						����2 �̵�
	*						����3 ����
  * @param  None
  * @retval None
  */
void key_led(void){
		uint8_t keynum = key_get_num();
		switch(keynum){
			case 1:	led_turn(RED_PORT, RED_PIN);break;
			case 2:	led_turn(GREEN_PORT, GREEN_PIN);break;
			case 3:	led_turn(BLUE_PORT, BLUE_PIN);break;
			case 4:	buzzer_turn(BUZZER_PORT, BUZZER_PIN); break;
			default:break;
		}
	}

	/**
    * @brief  ϵͳ��ʱ��ʵ����ˮ��
    * @param  None
    * @retval None
    */
void water_led(void){
		if(num == 4){
			num = 1;
		}
		else{
			num++;
		}
		led_enable(num);
		if(num - 1 == 0){
			led_disable(4);
		}
		else{
			led_disable(num - 1);
		}
		
	}

















