#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/uaccess.h>
#include <linux/sched.h>

dev_t mydev;
struct cdev mycdev;
struct file_operations myfops;
struct class *myclass;
unsigned int irq_num;
int cond;

//创建一个等待队列
DECLARE_WAIT_QUEUE_HEAD(mywait);

irqreturn_t myfunc(int num, void *args)
{
	printk("按键被按下\n");
	cond = 1;
	return 0;
}

int myopen (struct inode *inode, struct file *file)
{
	int ret;
	//gpio转中断号
	irq_num = gpio_to_irq(EXYNOS4_GPX3(2));
	if(irq_num < 0)
	{
		printk("中断号转换失败\n");
		return -1;
	}
	printk("gpio转中断号成功\n");

	//使能中断号
	enable_irq(irq_num);

	//向内核注册一个中断号
	ret = request_irq(irq_num, myfunc, IRQF_TRIGGER_FALLING, "keytest", NULL);
	if(ret < 0)
	{
		printk("中断号注册失败\n");
		return -1;
	}
	printk("open执行完毕\n");
	return 0;
}

int myclose (struct inode *inode, struct file *file)
{
	//取消中断的注册
	free_irq(irq_num, NULL);

	//使能中断
	disable_irq(irq_num);

	return 0;
}

ssize_t myread (struct file *file, char __user *buf, size_t size, loff_t *loff)
{
	int value, ret;
	wait_event_interruptible(mywait, cond);
	printk("阻塞解除\n");
	value = gpio_get_value(EXYNOS4_GPX3(2));
	ret = copy_to_user(buf, &value, 4);
	cond = 0;
	return 0;
}

static int __init mykey_init(void)
{
	//申请设备号
	alloc_chrdev_region(&mydev, 0, 1, "mykey");
	printk("申请到的设备号 %d\n", mydev);
	printk("主设备号 %d\n", MAJOR(mydev));
	printk("次设备号 %d\n", MINOR(mydev));
	
	//初始化核心结构体
	myfops.owner = THIS_MODULE;
	myfops.open = myopen;
	myfops.release = myclose;
	myfops.read = myread;
	cdev_init(&mycdev, &myfops);

	//向设备注册核心结构体
	cdev_add(&mycdev, mydev, 1);

	//创建类结构体
	myclass = class_create(THIS_MODULE, "mykey");
	if(myclass == NULL)
	{
		printk("创建类结构体失败\n");
		return -1;
	}

	//创建设备文件
	device_create(myclass, NULL, mydev, NULL, "mykey");
	return 0;
}

static void __exit mykey_exit(void)
{
	//注销设备文件
	device_destroy(myclass, mydev);

	//注销类结构体
	class_destroy(myclass);

	//取消注册
	cdev_del(&mycdev);

	//释放设备好
	unregister_chrdev_region(mydev, 1);
}

module_init(mykey_init);
module_exit(mykey_exit);
MODULE_LICENSE("GPL");