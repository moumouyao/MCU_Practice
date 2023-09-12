#include "exti.h"
#include "buzzer.h"

uint8_t k1 = 0, k2 = 0, k3 = 0, k4 = 0;
/**
  * @brief  把PA0设置成外部中断 
	*						抢占优先级 0		响应优先级 0
  * @param  None
  * @retval None
  */
	void key1_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//开启复用时钟
		AFIO->EXTICR[0] &= ~(0XF << 0);	//配置PA0对应的中断线0
		EXTI->IMR |= 1 << 0;	//开启PA0的中断屏蔽寄存器
		EXTI->RTSR |= 1 << 0;	//设置上升沿触发
		EXTI->FTSR  &= 0 << 0;	//关闭下降沿触发
		EXTI->PR |= 1 << 0; //清除挂起标志位
		NVIC_SetPriorityGrouping(2);
		NVIC_SetPriority(EXTI0_IRQn, 0);	//抢占优先级 0  响应优先级 0
		NVIC_EnableIRQ(EXTI0_IRQn);		//使能外部中断0
	}
	
	/**
    * @brief  按键1中断处理函数
    * @param  None
    * @retval 按键按下，标志位k1反转
    */
	void EXTI0_IRQHandler(void){
		if((EXTI->PR & 1 << 0) == 1){
			EXTI->PR |= 1 << 0; //清除挂起标志位
			if(k1 ==  0){
				k1 = 1;
			}
			else{
				k1 = 0;
			}
			
		}
	}
	
	/**
  * @brief  把PC0设置成外部中断 
	*						抢占优先级 0		响应优先级 0
  * @param  None
  * @retval None
  */
	void key2_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//开启复用时钟
		AFIO->EXTICR[1] &= ~(0XF << 0);	//配置PC4	对应的中断线4
		AFIO->EXTICR[1] |= (0X2  << 0);
		EXTI->IMR |= 1 << 4;	//开启PC4的中断屏蔽寄存器
		EXTI->FTSR  |= 1 << 4;	//开启下降沿触发
		EXTI->PR |= 1 << 4; //清除挂起标志位
		NVIC_SetPriority(EXTI4_IRQn, 0);	//抢占优先级 0  响应优先级 0
		NVIC_EnableIRQ(EXTI4_IRQn);		//使能外部中断0
	}
	
	/**
    * @brief  按键2中断处理函数
    * @param  None
    * @retval 按键按下，标志位k2反转
    */
	void EXTI4_IRQHandler(void){
		if((EXTI->PR & 1 << 4) != 0){
			EXTI->PR |= 1 << 4; //清除挂起标志位
			if(k2 ==  0){
				k2 = 1;
			}
			else{
				k2 = 0;
			}
			
		}
	}
	
		/**
  * @brief  把PC5设置成外部中断 
	*						抢占优先级 0		响应优先级 0
  * @param  None
  * @retval None
  */
	void key3_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//开启复用时钟
		AFIO->EXTICR[1] &= ~(0XF << 4);	//配置PC5	对应的中断线4
		AFIO->EXTICR[1] |= (0X2  << 4);
		EXTI->IMR |= 1 << 5;	//开启PC5的中断屏蔽寄存器
		EXTI->FTSR  |= 1 << 5;	//开启下降沿触发
		EXTI->PR |= 1 << 5; //清除挂起标志位
		NVIC_SetPriority(EXTI9_5_IRQn, 0);	//抢占优先级 0  响应优先级 0
		NVIC_EnableIRQ(EXTI9_5_IRQn);		//使能外部中断0
	}
	
			/**
  * @brief  把PC6设置成外部中断 
	*						抢占优先级 0		响应优先级 0
  * @param  None
  * @retval None
  */
	void key4_exit_init(void){
		RCC->APB2ENR |= 1 << 0;	//开启复用时钟
		AFIO->EXTICR[1] &= ~(0XF << 8);	//配置PC6	对应的中断线6
		AFIO->EXTICR[1] |= (0X2  << 8);
		EXTI->IMR |= 1 << 6;	//开启PC6的中断屏蔽寄存器
		EXTI->FTSR  |= 1 << 6;	//开启下降沿触发
		EXTI->PR |= 1 << 6; //清除挂起标志位
		NVIC_SetPriority(EXTI9_5_IRQn, 0);	//抢占优先级 0  响应优先级 0
		NVIC_EnableIRQ(EXTI9_5_IRQn);		//使能外部中断0
	}
	
	/**
    * @brief  按键3按键4中断处理函数
    * @param  None
    * @retval None
    */
	void EXTI9_5_IRQHandler(void){
		if((EXTI->PR & 1 << 5) != 0){		//外部中断5触发
			EXTI->PR |= 1 << 5; //清除挂起标志位
			if(k3 ==  0){
				k3 = 1;
			}
			else{
				k3 = 0;
			}
			
		}
		if((EXTI->PR & 1 << 6) != 0){		//外部中断5触发
			EXTI->PR |= 1 << 6; //清除挂起标志位
			if(k4 ==  0){
				k4 = 1;
			}
			else{
				k4 = 0;
			}
			
		}
	}
	
	/**
    * @brief  返回按键的标志位
    * @param  keyx 要返回的按键 1 2 3 4
    * @retval val	按键1标志位
    */
	uint8_t get_key_val(uint8_t key){
		switch(key){
			case KEY1: return k1;
			case KEY2: return k2;
			case KEY3: return k3;
			case KEY4: return k4;
			default: return 0;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
