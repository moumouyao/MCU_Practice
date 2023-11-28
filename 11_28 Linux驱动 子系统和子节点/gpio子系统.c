#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/gpio.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>



dev_t mydev[4];
struct file_operations myfops[4];
struct cdev mycdev[4];
struct class *myclass = NULL;

int myopen0 (struct inode *inode, struct file *file){
	
	gpio_set_value(EXYNOS4X12_GPM4(0), 0);
	return 0;
}

int myopen1 (struct inode *inode, struct file *file){
	
	gpio_set_value(EXYNOS4X12_GPM4(1), 0);
	return 0;
}

int myopen2 (struct inode *inode, struct file *file){
	
	gpio_set_value(EXYNOS4X12_GPM4(2), 0);
	return 0;
}

int myopen3 (struct inode *inode, struct file *file){
	
	gpio_set_value(EXYNOS4X12_GPM4(3), 0);
	return 0;
}


int myclose0 (struct inode *inode, struct file *file){

	gpio_set_value(EXYNOS4X12_GPM4(0), 1);
	return 0;
}

int myclose1 (struct inode *inode, struct file *file){

	gpio_set_value(EXYNOS4X12_GPM4(1), 1);
	return 0;
}

int myclose2 (struct inode *inode, struct file *file){

	gpio_set_value(EXYNOS4X12_GPM4(2), 1);
	return 0;
}

int myclose3 (struct inode *inode, struct file *file){

	gpio_set_value(EXYNOS4X12_GPM4(3), 1);
	return 0;
}





static int __init myled_init(void){

	int ret, i;

	//gpio口设置
	for(i = 0; i < 4; i++){
		//申请io口
		ret = gpio_request(EXYNOS4X12_GPM4(0), "led1");
		if(ret < 0){
			printk("io口申请失败\n");
		}
		
		//设置引脚的工作模式为输出
		gpio_direction_output(EXYNOS4X12_GPM4(0), 1);

		//设置引脚值
		gpio_set_value(EXYNOS4X12_GPM4(0), 1);
	}

	//申请设备号
	alloc_chrdev_region(mydev, 0, 4, "myled");
	mydev[1] = mydev[0] + 1;
	mydev[2] = mydev[1] + 1;
	mydev[3] = mydev[2] + 1;
	printk("1 %d\n2 %d\n3 %d\n4 %d\n", mydev[0], mydev[1], mydev[2], mydev[3]);

	//初始化Linux2.6核心结构体
	myfops[0].owner = THIS_MODULE;
	myfops[1].owner = THIS_MODULE;
	myfops[2].owner = THIS_MODULE;
	myfops[3].owner = THIS_MODULE;

	myfops[0].open = myopen0;
	myfops[1].open = myopen1;
	myfops[2].open = myopen2;
	myfops[3].open = myopen3;

	myfops[0].release = myclose0;
	myfops[1].release = myclose1;
	myfops[2].release = myclose2;
	myfops[3].release = myclose3;

	cdev_init(&mycdev[0], &myfops[0]);
	cdev_init(&mycdev[1], &myfops[1]);
	cdev_init(&mycdev[2], &myfops[2]);
	cdev_init(&mycdev[3], &myfops[3]);

	//向内核注册核心结构体
	cdev_add(&mycdev[0], mydev[0], 1);
	cdev_add(&mycdev[1], mydev[1], 1);
	cdev_add(&mycdev[2], mydev[2], 1);
	cdev_add(&mycdev[3], mydev[3], 1);

	//创建类结构体
	myclass = class_create(THIS_MODULE, "myled");
	if(myclass == NULL){
		printk("创建类结构体失败\n");
		return -1;
	}

	//创建设备文件
	device_create(myclass, NULL, mydev[0], NULL, "myled0");
	device_create(myclass, NULL, mydev[1], NULL, "myled1");
	device_create(myclass, NULL, mydev[2], NULL, "myled2");
	device_create(myclass, NULL, mydev[3], NULL, "myled3");
	
	return 0;
}

static void __exit myled_exit(void){

	//卸载io口
	gpio_free(EXYNOS4X12_GPM4(0));

	//注销设备文件
	device_destroy(myclass, mydev[0]);
	device_destroy(myclass, mydev[1]);
	device_destroy(myclass, mydev[2]);
	device_destroy(myclass, mydev[3]);

	//注销类结构体
	class_destroy(myclass);

	//取消Linux2.6注册
	cdev_del(&mycdev[0]);
	cdev_del(&mycdev[1]);
	cdev_del(&mycdev[2]);
	cdev_del(&mycdev[3]);

	//释放设备号
	unregister_chrdev_region(mydev[0], 1);
	unregister_chrdev_region(mydev[1], 1);
	unregister_chrdev_region(mydev[2], 1);
	unregister_chrdev_region(mydev[3], 1);
}

module_init(myled_init);
module_exit(myled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYY");


