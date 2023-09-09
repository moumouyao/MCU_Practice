#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"

void waterfall_light(void);

int main(){
buuzer_init();
	
	//��ˮ��
	waterfall_light();
}

//��ˮ��
void waterfall_light(void){
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);
	led_init(LED4);
	while(1){
		led_enable(LED1);
		buzzer_enable();	//����������
		Delay_ms(200);
		led_disable(LED1);
		buzzer_disable();	//�رշ�����
		Delay_ms(200);
		led_enable(LED2);
		Delay_ms(200);
		led_disable(LED2);
		Delay_ms(200);
		led_enable(LED3);
		Delay_ms(200);
		led_disable(LED3);
		Delay_ms(200);
		led_enable(LED4);
		Delay_ms(200);
		led_disable(LED4);
		Delay_ms(200);
	}
}
