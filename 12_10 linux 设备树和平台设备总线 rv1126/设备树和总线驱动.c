#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

struct platform_driver mydrv;
struct resource *myres = NULL;
unsigned int GPM4_CON;
int act_level_on, act_level_off, io_start, io_end;
dev_t mydev;
struct cdev mycdev;
struct file_operations myfops;
struct class *myclass = NULL;

int myopen(struct inode *inode, struct file *file)
{
	//设置引脚值
	gpio_set_value(myres->end, act_level_on);
	return 0;
}
int myclose(struct inode *inode, struct file *file)
{
	//设置引脚值
	gpio_set_value(myres->end, act_level_off);
	return 0;
}


int myprobe(struct platform_device * dev){
	int ret;
	printk("设备层和驱动层匹配成功\n");

	//读取有效电平
	myres = platform_get_resource(dev, IORESOURCE_MEM, 1);
	act_level_off = myres->start;
	act_level_on = myres->end;

	//读取引脚编号
	myres = platform_get_resource(dev, IORESOURCE_MEM, 0);
	io_start = myres->start;
	io_end = myres->end;


	//申请io口
	ret = gpio_request(myres->end, "beep");
	if(ret < 0){
		printk("io口申请失败\n");
		return -1;
	}

	//设置工作模式为输出模式
	gpio_direction_output(myres->end, 0);

	
	//申请设备号
	alloc_chrdev_region(&mydev, 0, 1, "myled");
	printk("设备号 %d\n", mydev);

	//初始化Linux2.6核心结构体
	myfops.owner = THIS_MODULE;
	myfops.open = myopen;
	myfops.release = myclose;
	cdev_init(&mycdev, &myfops);

	//向内核注册Linux2.6结构体
	cdev_add(&mycdev, mydev, 1);

	//创建一个类结构体
	myclass = class_create(THIS_MODULE, "myled");
	if(myclass == NULL){
		printk("创建类结构体失败\n");
		return -1;
	}

	//创建设备文件
	device_create(myclass, NULL, mydev, NULL, "myled");
	return 0;
	
}

int myremove(struct platform_device * dev){

	printk("设备层和驱动层有一端被卸载\n");

	//注销设备文件
	device_destroy(myclass, mydev);

	//注销类结构体
	class_destroy(myclass);

	//取消Linux2.6注册
	cdev_del(&mycdev);

	//释放设备号
	unregister_chrdev_region(mydev, 1);
	return 0;
}


static int __init myled_driver_init(void){
	//初始化并注册核心结构体
	mydrv.driver.name = "mybeep";
	mydrv.probe = myprobe;
	mydrv.remove = myremove;
	platform_driver_register(&mydrv);
	return 0;
}

static void __exit myled_driver_exit(void){
	platform_driver_unregister(&mydrv);
}

module_init(myled_driver_init);
module_exit(myled_driver_exit);
MODULE_LICENSE("GPL");

