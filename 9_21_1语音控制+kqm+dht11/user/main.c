#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
#include "interrupt.h"
#include "timer.h"
#include "usart.h"
#include <string.h>
#include "kqm.h"
#include "su_03t.h"
#include "dht11.h"

int main(){
	sys_tick_init();
	usart_init();
	led_init(LED1);
	kqm_init();
	su_o3t_init();
	buzzer_init();
	dth11_init();

	usart_TXpacket[0] = 0x41;
	usart_TXpacket[1] = 0x42;
	usart_TXpacket[2] = 0x43;
	usart_TXpacket[3] = 0x44;
	usart_send_hex_packet();
	while(1){
		
			su_time_scale(15);
		kqm_time_scale(18);
		//printf("%d",dht_get_val());
			dht_time_scale(500);
			//Delay_ms(2000);
	
}

}












