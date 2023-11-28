#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/io.h>

struct miscdevice led_misc;		//杂项结构体
struct file_operations led_fops;	//文件操作集合结构体

void __iomem *GPM4_CON = NULL;	//GPM4控制寄存器
void __iomem *GPM4_DAT = NULL;	//GPM4数据寄存器

//开灯函数
int led_open (struct inode *inode, struct file *file){

	printk("灯被打开\n");
	*((unsigned int *)GPM4_DAT) &= ~(0xf);
	return 0;
}

//关灯函数
int led_close (struct inode *inode, struct file *file){
	printk("灯被关闭\n");
	*((unsigned int *)GPM4_DAT) |= (0xf);
}

static int __init myled_init(void){
	printk("led灯加载函数\n");

	//地址映射
	GPM4_CON = ioremap(0x110002e0, 4);
	GPM4_DAT = ioremap(0x110002e4, 1);

	//io口配置
	*((unsigned int *)GPM4_CON) &= ~(0xffff);
	*((unsigned int *)GPM4_CON) |= 0x1111;
	*((unsigned int *)GPM4_DAT) |= 0xf;

	//向内核注册一个杂项
	led_fops.owner = THIS_MODULE;	//模块所有者
	led_fops.open = led_open;		//开灯
	led_fops.release = led_close;	//关灯
	
	led_misc.minor = 255;	//次设备号,由系统分配
	led_misc.name = "led_dev";	//dev目录下的设备文件名
	led_misc.fops = &led_fops;	//文件操作集合

	misc_register(&led_misc);

	return 0;
}

static void __exit myled_exit(void){
	printk("led灯卸载函数\n");
	misc_deregister(&led_misc);
}

module_init(myled_init);
module_exit(myled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYY");