#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>


int main(){

	int key_fd = 0, num = 0;
	key_fd = open("/dev/mykey", O_RDWR);
	if(key_fd < 0){
		printf("打开mykey失败\n");
		perror("open");
	}
		
	while(1){
		read(key_fd, &num, 4);
		if(num != 0){
			printf("按键%d按下\n", num);
			num = 0;
		}		
		}
	return 0;
}

