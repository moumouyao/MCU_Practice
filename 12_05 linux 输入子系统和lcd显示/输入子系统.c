#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/timer.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/jiffies.h>
#include <linux/gpio.h>


struct input_dev *myinput = NULL;
int irq_num;
struct timer_list mytimer;

void mytimer_func(unsigned long data){
	if(gpio_get_value(EXYNOS4_GPX3(2)) == 0){
		input_report_key(myinput, KEY_1, 1);
	}
	else{
		input_report_key(myinput, KEY_1, 0);
	}
	input_sync(myinput);
}

irqreturn_t myirq_func(int num, void * data){

	mod_timer(&mytimer, jiffies + msecs_to_jiffies(15));
	
	return 0;
}


static int __init myinput_init(void){
	int ret;

	//初始化输入子系统的核心结构体
	myinput = input_allocate_device();
	myinput->name = "yyy";

	//向内核注册输入子系统
	set_bit(EV_KEY, myinput->evbit);	//按键事件
	set_bit(EV_REP, myinput->evbit);	//重复事件
	
	set_bit(KEY_1, myinput->keybit);
	ret = input_register_device(myinput);

	//获取中断号
	irq_num = gpio_to_irq(EXYNOS4_GPX3(2));

	//使能中断号
	enable_irq(irq_num);

	//向内核注册中断号
	ret = request_irq(irq_num, myirq_func, IRQ_TYPE_EDGE_BOTH, "my_input", NULL);

	//初始化定时器
	mytimer.expires = jiffies + 1 * HZ;
	mytimer.function = mytimer_func;
	init_timer(&mytimer);
	
	return 0;
}

static void __exit myinput_exit(void){
	//取消注册
	input_unregister_device(myinput);
}

module_init(myinput_init);
module_exit(myinput_exit);
MODULE_LICENSE("GPL");






