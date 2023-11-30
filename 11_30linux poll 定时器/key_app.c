#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>



int main(){

	int key_fd = 0, num = 0;
	struct pollfd mypoll;
	key_fd = open("/dev/mykey", O_RDWR);
	mypoll.fd = key_fd;
	mypoll.events = POLLIN;

	if(key_fd < 0){
		printf("打开mykey失败\n");
		perror("open");
	}
		
	while(1){
		poll(&mypoll,1,-1);	
		if(mypoll.revents == POLLIN)
		{
			mypoll.revents = 0;

			read(key_fd, &num, 4);
			if(num != 0){
				printf("按键%d按下\n", num);
				num = 0;
			}
		}		
	}
	return 0;
}


