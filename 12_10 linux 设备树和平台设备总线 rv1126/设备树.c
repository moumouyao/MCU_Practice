#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>

struct device_node *mynode = NULL;
int gpio_num = 0;

static int __init mytest_init(void){
	
	int ret;
	//通过路径查找设备树节点
	mynode = of_find_node_by_path("/bigbeep");
	if(mynode == NULL){
		printk("获取结构体地址失败\n");
		return -1;
	}

	//从设备树中获取gpio编号
	gpio_num = of_get_named_gpio(mynode, "gpios", 0);
	printk("name=%s\n", mynode->);
	printk("引脚编号 %d\n", gpio_num);

	//申请io口
	ret = gpio_request(gpio_num, "beep");
	if(ret < 0){
		printk("io口申请失败\n");
		return -1;
	}

	//设置工作模式为输出模式
	gpio_direction_output(gpio_num, 0);

	//设置引脚值
	gpio_set_value(gpio_num, 1);
	
	return 0;
}

static void __exit mytest_exit(void){

}

module_init(mytest_init);
module_exit(mytest_exit);
MODULE_LICENSE("GPL");


