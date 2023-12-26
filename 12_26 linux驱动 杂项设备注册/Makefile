obj-m += bp_dev.o
KDIR:=/home/yyy/linux/1lunxu_diver/11_21/linux-3.5 
all:
	make -C $(KDIR) M=$(PWD) modules
	arm-linux-gcc bp_app.c -o bp_app
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.markers *.order bp_app
