#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>

extern unsigned char gImage_img[1152008];
struct fb_var_screeninfo fv;
struct fb_fix_screeninfo fs;
int fd;
int *lcd_base = NULL;

void show_pic(char *data, int w, int h){
	int i, j;
	int *p = lcd_base;
	for(j = 0; j < h; j++){
		for(i = 0; i < w; i++){
			p[i] = data[i * 3 + j * w * 3] | data[i * 3 + j *w * 3 + 1] << 8 | data[i * 3 + j * w *3 +2] << 16;
		}
		p += fv.xres_virtual;
	}
}

int main(){
	fd = open("/dev/fb0", O_RDWR);
	if(fd < 0){
		perror("open");
		return -1;
	}

	ioctl(fd, FBIOGET_VSCREENINFO, &fv);
	printf("显示屏的真实长宽为 %d * %d\n", fv.xres, fv.yres);
	printf("显示器的虚拟的长宽为 %d * %d\n", fv.xres_virtual, fv.yres_virtual);
	printf("一个像素点占的位数 %d\n", fv.bits_per_pixel);

	ioctl(fd, FBIOGET_FSCREENINFO, &fs);
	printf("一行的位数 %d\n", fs.line_length);

	lcd_base = mmap(NULL, fv.xres_virtual * fv.yres_virtual * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	show_pic(gImage_img, 800, 480);

	return 0;

}
