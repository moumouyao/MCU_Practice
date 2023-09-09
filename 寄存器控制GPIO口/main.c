#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"

void waterfall_light(void);

int main(){
buuzer_init();
	
	//流水灯
	waterfall_light();
}

//流水灯
void waterfall_light(void){
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);
	led_init(LED4);
	while(1){
		led_enable(LED1);
		buzzer_enable();	//开启蜂鸣器
		Delay_ms(200);
		led_disable(LED1);
		buzzer_disable();	//关闭蜂鸣器
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
