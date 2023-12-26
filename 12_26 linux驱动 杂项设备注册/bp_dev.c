#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/io.h>

void __iomem *GPD0_CON = NULL;	//控制寄存器
void __iomem *GPD0_DAT = NULL;	//数据寄存器

struct file_operations bp_fops;
struct miscdevice bp_misc;

//开启蜂鸣器函数
int bp_open (struct inode *inode, struct file *file){
	printk("蜂鸣器开启\n");
	*((unsigned int *)GPD0_DAT) |= 0x1;
	return 0;
}

//蜂鸣器关闭函数
int bp_close (struct inode *inode, struct file *file){
	printk("蜂鸣器关闭\n");
	*((unsigned int *)GPD0_DAT) &= ~(0x1);
	return 0;
}




static int __init bp_init(void){
	printk("加载蜂鸣器模块\n");

	//地址映射
	GPD0_CON = ioremap(0x114000a0, 2);
	GPD0_DAT = ioremap(0x114000a4, 1);

	//寄存器设置
	*((unsigned int *)GPD0_CON) &= ~(0xf);
	*((unsigned int *)GPD0_CON) |= (0x1);
	*((unsigned int *)GPD0_DAT) &= (0x1);

	//向内核注册一个杂项设备
	bp_fops.open = bp_open;	//打开蜂鸣器
	bp_fops.release = bp_close;	//关闭蜂鸣器
	bp_fops.owner = THIS_MODULE;	//模块所有者
	
	bp_misc.minor = 255;	//系统分配次设备号
	bp_misc.name = "bp_dev";	//设备文件名
	bp_misc.fops = &bp_fops;	//文件操作集合
	misc_register(&bp_misc);
	
	return 0;
}

static void __exit bp_exit(void){
	printk("卸载蜂鸣器模块\n");
	misc_deregister(&bp_misc);
	
}

module_init(bp_init);
module_exit(bp_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYY");





