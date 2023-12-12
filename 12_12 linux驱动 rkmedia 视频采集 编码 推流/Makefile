HOME_SDK=/home/d/202/rv1126_rv1109_v2.2.0_20210825

C_FLAGS = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -DUSE_UPDATEENGINE=ON -DSUCCESSFUL_BOOT=ON  -DNDEBUG   -Wall -Wextra -Wshadow -ffast-math -fPIC -Werror -g -O0 -ggdb -gdwarf -funwind-tables -rdynamic

C_DEFINES = -DAUDIO_ALGORITHM_ENABLE -DLIBDRM -DRKAIQ

C_INCLUDES = -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/. -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/a3dlut -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/ablc -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/accm -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/acp -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/adebayer -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/adehaze -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/adpcc -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/ae -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/af -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/agamma -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/ahdr -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/aie -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/alsc -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/anr -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/aorb -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/asd -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/asharp -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/awb -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/common -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/iq_parser -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/uAPI -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/xcore -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/libdrm -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/include/easymedia -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/include/rkmedia -I$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/include -isystem $(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq -I$(HOME_SDK)/external/rkmedia/examples
LIBS=-L$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/examples/librtsp -Wl,-rpath,$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/examples/librtsp:$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/src:$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/examples/../src/rkaudio: $(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/build/rkmedia/src/libeasymedia.so.1.0.1  -lrtsp -ldrm -lrockchip_mpp -lliveMedia -lgroupsock -lBasicUsageEnvironment -lUsageEnvironment -lpthread -lasound -lRKAP_3A -lRKAP_ANR -lRKAP_Common -lv4l2 -lrga -lRKAP_3A -lRKAP_ANR -lRKAP_Common -lv4l2 -lrga -lrknn_runtime -lrknn_api -lrockface -lsqlite3 -lmd_share -lod_share -lrockx $(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/librkaiq.so 
#LIBS+=-lmyrtmp -L./ -lstdc++
ROOTDIR = $(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot

		
GCC_DIR=\
	$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/bin/arm-linux-gnueabihf-gcc
G++_DIR=\
	$(HOME_SDK)/buildroot/output/rockchip_rv1126_rv1109/host/bin/arm-linux-gnueabihf-g++

INCLUDE_DIR = -I$(HOME_SDK)/external/rkmedia/include \
	      -I$(HOME_SDK)/external/rkmedia/examples \
		-I$(HOME_SDK)/external/rkmedia/include/rkmedia\
		-I$(HOME_SDK)/external/rkmedia/include/easymedia
#OBJ:=myvideo_rtsp_test
OBJ:=main
$(OBJ):$(OBJ).c
	
	$(GCC_DIR) -c $(OBJ).c -o $(OBJ).o $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) --sysroot=$(ROOTDIR) 
	$(GCC_DIR) -c sample_common_isp.c -o sample_common_isp.o $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) --sysroot=$(ROOTDIR) 
	$(GCC_DIR) -c sample_fake_isp.c -o sample_fake_isp.o $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) --sysroot=$(ROOTDIR) 
	$(G++_DIR) $(OBJ).o sample_common_isp.o sample_fake_isp.o -o $(OBJ) $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) $(LIBS)

