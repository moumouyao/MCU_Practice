#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){

	int bp_fd = 0;
	while(1){
		bp_fd = open("/dev/bp_dev", O_RDWR);
		if(bp_fd < 0){
			printf("打开bp_dev失败\n");
			perror("open");
		}
		printf("开启蜂鸣器\n");
		sleep(1);
		close(bp_fd);
		printf("关闭蜂鸣器\n");
		sleep(1);
	}
	return 0;
}

