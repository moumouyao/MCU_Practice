#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){

	int led_fd  =0;
	while(1){
		led_fd = open("/dev/led_dev", O_RDWR);
		if(led_fd < 0){
			printf("打开led_dev失败\n");
		}
		printf("开灯\n");
		sleep(1);
		close(led_fd);
		printf("关灯\n");
		sleep(1);
	}
	return 0;
}