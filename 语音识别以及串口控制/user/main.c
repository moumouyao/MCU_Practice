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


int main(){
	sys_tick_init();
	usart_init();
	led_init(LED1);
	kqm_init();
	su_o3t_init();
//	uint8_t arry[] = {0x41, 0x42, 0x43, 0x44};
//	usart_send_array(arry, 4);
//	usart_send_string("hello wrold!");
//	usart_sendbit(0x41);
//	usart_send_string("d!");
//	usart_send_num(12345, 5);
//	printf("NUM = %d\r\n", 666);
//	usart_printf("Ò¦ÀÖÒã = %d\r\n", 777);
//	usart_printf("ÄãºÃ£¬ÊÀ½ç");
	usart_TXpacket[0] = 0x41;
	usart_TXpacket[1] = 0x42;
	usart_TXpacket[2] = 0x43;
	usart_TXpacket[3] = 0x44;
	usart_send_hex_packet();
	while(1){
		vioce_analysis();
		//air_analysis();
	
}

}












