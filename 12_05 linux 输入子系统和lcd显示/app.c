#include <stdio.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int fd;
struct input_event myevent;
int main(){
	fd = open("/dev/input/event3", O_RDWR);
	if(fd < 0){
		perror("open");
		return -1;
	}
	while(1){
		read(fd, &myevent, sizeof(myevent));
		if(myevent.type == EV_KEY){
			if(myevent.value == 1){
				printf("按键1按下\n");
			}
			else{
				printf("按键1松开\n");
			}
		}
		if(myevent.type == EV_SYN){
			printf("上报事件同步\n");
		}
	}
	return 0;
}
