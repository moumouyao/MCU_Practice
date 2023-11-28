#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>

dev_t  mydev;
int count;
struct cdev mycdev;
struct file_operations myfops;
struct class *myclass = NULL;

//open函数实现，开灯，流水灯效果
int myopen (struct inode *inode, struct file *file){
	if(count == 4)
		count = 0;
	gpio_set_value(EXYNOS4X12_GPM4(count), 0);
	gpio_set_value(EXYNOS4_GPD0(0), 1);
	count++;
	printk("开灯%d\n", count);
	return 0;
}

//close函数实现，关灯，流水灯效果
int myclose (struct inode *inode, struct file *file){
	gpio_set_value(EXYNOS4X12_GPM4(count - 1), 1);
	gpio_set_value(EXYNOS4_GPD0(0), 0);
	printk("关灯%d\n", count - 1);
	return 0;
}


static int __init myled_init(void){
	//申请设备号
	
	alloc_chrdev_region(&mydev, 0, 1, "myled");
	printk("申请到的设备号为 %d\n", mydev);
	printk("主设备号 %d\n", MAJOR(mydev));
	printk("次设备号 %d\n", MINOR(mydev));

	//初始化Linux2.6的核心结构体
	myfops.owner = THIS_MODULE;
	myfops.open = myopen;
	myfops.release = myclose;
	cdev_init(&mycdev, &myfops);

	//向内核注册一个Linux2.6核心结构体
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

static void __exit myled_exit(void){
	//注销设备文件
	device_destroy(myclass, mydev);

	//注销类结构体
	class_destroy(myclass);

	//取消Linux2.6注册
	cdev_del(&mycdev);

	//释放设备号
	unregister_chrdev_region(mydev, 1);
}

module_init(myled_init);
module_exit(myled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYY");


