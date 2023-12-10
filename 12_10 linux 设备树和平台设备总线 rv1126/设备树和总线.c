#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>



struct platform_device mypdev;
struct resource myres[2];
struct device_node *mynode = NULL;
int gpio_num = 0;


void myrelease(struct device *dev){

}

static int __init mybeep_dev_init(void){
	//通过路径查找设备树节点
	mynode = of_find_node_by_path("/bigbeep");
	if(mynode == NULL){
		printk("获取结构体地址失败\n");
		return -1;
	}
	
	//从设备树中获取gpio编号
	gpio_num = of_get_named_gpio(mynode, "gpios", 0);
	printk("引脚编号 %d\n", gpio_num);
	
	//注册设备层

	//有效电平
	myres[0].start = 0;
	myres[0].end = gpio_num;
	myres[0].flags = IORESOURCE_MEM;
	myres[0].name = "beep0";
	printk("1\n");

	//引脚编号
	myres[1].start = 0;
	myres[1].end = 1;
	myres[1].flags = IORESOURCE_MEM;
	myres[1].name = "beep1";
	printk("2\n");

	//初始化核心结构体
	mypdev.name = "mybeep";
	mypdev.id = -1;
	mypdev.num_resources = 2;
	mypdev.dev.release = myrelease;
	mypdev.resource = myres;
	platform_device_register(&mypdev);
	printk("3\n");
	return 0;
}

static void __exit mybeep_dev_exit(void){
	//卸载设备层核心结构体
	platform_device_unregister(&mypdev);
}

module_init(mybeep_dev_init);
module_exit(mybeep_dev_exit);
MODULE_LICENSE("GPL");

