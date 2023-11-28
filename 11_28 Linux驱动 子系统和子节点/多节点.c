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

int myopen(struct inode *inode, struct file *file){
	int i;
	for(i = 0; i < 4; i++){
		if(inode->i_rdev == mydev[i]){
			gpio_set_value(EXYNOS4X12_GPM4(i), 0);
			break;
		}
		
	}
	
	return 0;
}


int myclose(struct inode *inode, struct file *file){
	int i;
	for(i = 0; i < 4; i++){
		if(inode->i_rdev == mydev[i]){
			gpio_set_value(EXYNOS4X12_GPM4(i), 1);
			break;
		}
		
	}
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

	
	for(i = 0; i < 4; i++){
		myfops[i].owner = THIS_MODULE;
		myfops[i].open = myopen;
		myfops[i].release = myclose;

		//初始化Linux2.6核心结构体
		cdev_init(&mycdev[i], &myfops[i]);

		//向内核注册核心结构体
		cdev_add(&mycdev[i], mydev[i], 1);
		
	}

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
	int i;

	//卸载io口
	for(i = 0; i < 4; i++){
		gpio_free(EXYNOS4X12_GPM4(i));
	}
	
	//注销设备文件
	for(i = 0; i < 4; i++){
		device_destroy(myclass, mydev[i]);
	}

	//注销类结构体
	class_destroy(myclass);

	//取消Linux2.6注册
	for(i = 0; i < 4; i++){
		cdev_del(&mycdev[i]);
	}

	//释放设备号
	for(i = 0; i < 4; i++){
		unregister_chrdev_region(mydev[i], 1);
	}
}

module_init(myled_init);
module_exit(myled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYY");



