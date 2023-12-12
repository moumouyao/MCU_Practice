#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "common/sample_common.h"
#include "librtsp/rtsp_demo.h"
#include "rkmedia_api.h"
#include "rkmedia_venc.h"

FILE *fp = NULL;
RK_BOOL bMultictx = RK_FALSE;
RK_CHAR *pIqfilesPath = "/oem/etc/iqfiles";		//配置文件
int quit = 0;
rtsp_demo_handle g_rtsplive = NULL;
static rtsp_session_handle g_rtsp_session;


void video_packet_cb(MEDIA_BUFFER mb) {
  static RK_S32 packet_cnt = 0;
  if (quit)
    return;

  printf("#Get packet-%d, size %zu\n", packet_cnt, RK_MPI_MB_GetSize(mb));
	//推流
  if (g_rtsplive && g_rtsp_session) {
    rtsp_tx_video(g_rtsp_session, RK_MPI_MB_GetPtr(mb), RK_MPI_MB_GetSize(mb),
                  RK_MPI_MB_GetTimestamp(mb));
    rtsp_do_event(g_rtsplive);
  }
  fwrite(RK_MPI_MB_GetPtr(mb), RK_MPI_MB_GetSize(mb), 1, fp);
  RK_MPI_MB_ReleaseBuffer(mb);	//释放帧数据
  packet_cnt++;
}


int main(int argc, char *argv[]){
	argc = argc;
	argv = argv;
	int ret = 0;
	
	RK_U32 u32Width = 1920;	//视频采集的宽度	像素点
	RK_U32 u32Height = 1080;	//视频采集的高度	像素点
	//设置摄像头属性
	RK_CHAR *pDeviceName = "rkispp_scale0";	//摄像头
	rk_aiq_working_mode_t hdr_mode = RK_AIQ_WORKING_MODE_NORMAL;
    int fps = 30;	//每秒采集到视频帧的个数
    SAMPLE_COMM_ISP_Init(0, hdr_mode, bMultictx, pIqfilesPath);
    SAMPLE_COMM_ISP_Run(0);
    SAMPLE_COMM_ISP_SetFrameRate(0, fps);
	
	fp = fopen("test.h264", "w");
	if(fp == NULL){
		printf("打开录像文件失败\n");
		return -1;
	}
	//初始化推流服务器
	g_rtsplive = create_rtsp_demo(554);	//设置推流端口
	g_rtsp_session= rtsp_new_session(g_rtsplive, "/live/main_stream");//推流的路径
	rtsp_set_video(g_rtsp_session, RTSP_CODEC_ID_VIDEO_H264, NULL, 0);
	
	//同步时间
	rtsp_sync_video_ts(g_rtsp_session, rtsp_get_reltime(), rtsp_get_ntptime());
	
	RK_MPI_SYS_Init();	//初始化remedia的系统
	
	
	//设置vi通道的属性
	VI_CHN_ATTR_S pstChnAttr;
	pstChnAttr.pcVideoNode = pDeviceName;	//摄像头的节点
	pstChnAttr.u32Width = u32Width;	//视频的宽
	pstChnAttr.u32Height = u32Height;	//视频的高
	pstChnAttr.enPixFmt = IMAGE_TYPE_NV12;	//采集的视频格式
	pstChnAttr.u32BufCnt = 3;	//缓冲帧的大小
	pstChnAttr.enBufType = VI_CHN_BUF_TYPE_MMAP;	//内存映射
	pstChnAttr.enWorkMode = VI_WORK_MODE_NORMAL;	//工作模式，正常
	ret = RK_MPI_VI_SetChnAttr(0, 0, &pstChnAttr);
	if(ret != 0){
		printf("设置vi通道的属性错误\n");
		return -1;
	}
	
	
	//使能vi通道
	ret = RK_MPI_VI_EnableChn(0, 0);
	if(ret != 0){
		printf("使能vi通道失败\n");
		return -1;
	}
	
	
	//创建编码通道
	VENC_CHN_ATTR_S stVencChnAttr;
	stVencChnAttr.stVencAttr.enType = RK_CODEC_TYPE_H264;//编码协议的类型
	stVencChnAttr.stVencAttr.imageType = IMAGE_TYPE_NV12;//采集的图像的类型
	stVencChnAttr.stVencAttr.u32VirWidth = u32Width;//虚拟的宽
	stVencChnAttr.stVencAttr.u32VirHeight = u32Height;//虚拟的高
	stVencChnAttr.stVencAttr.u32Profile = 77;//编码的等级
	//stVencChnAttr.stVencAttr.bByFrame = 
	stVencChnAttr.stVencAttr.u32PicWidth = u32Width;//真实的宽
	stVencChnAttr.stVencAttr.u32PicHeight = u32Height;//真实的高
	stVencChnAttr.stVencAttr.enRotation = 0;//旋转角度
	
	stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H264CBR;//工作模式
	stVencChnAttr.stRcAttr.stH264Cbr.u32Gop = 30;//gop组帧数
	stVencChnAttr.stRcAttr.stH264Cbr.u32SrcFrameRateNum = 30;//帧率
	stVencChnAttr.stRcAttr.stH264Cbr.u32SrcFrameRateDen = 1;
	stVencChnAttr.stRcAttr.stH264Cbr.fr32DstFrameRateNum = 30;
	stVencChnAttr.stRcAttr.stH264Cbr.fr32DstFrameRateDen = 1;
	stVencChnAttr.stRcAttr.stH264Cbr.u32BitRate = u32Width * u32Height;//分辨率
	
	ret = RK_MPI_VENC_CreateChn(0, &stVencChnAttr);
	if(ret != 0){
		printf("创建编码通道失败\n");
		return -1;
	}
	
	//注册编码通道的回调函数
	MPP_CHN_S pstChn;
	pstChn.enModId = RK_ID_VENC;//模块号
	pstChn.s32DevId = 0;//设备号 第一个摄像头
	pstChn.s32ChnId = 0;//通道号 第一个通道
	ret = RK_MPI_SYS_RegisterOutCb(&pstChn, video_packet_cb);
	if(ret != 0){
		printf("注册编码通道的回调函数失败\n");
		return -1;
	}
	
	
	//绑定venc通道
    MPP_CHN_S pstSrcChn, pstDestChn;
	pstSrcChn.enModId = RK_ID_VI;
	pstSrcChn.s32DevId = 0;
	pstSrcChn.s32ChnId = 0;
	
	pstDestChn.enModId = RK_ID_VENC;
	pstDestChn.s32DevId = 0;
	pstDestChn.s32ChnId = 0;
	ret = RK_MPI_SYS_Bind(&pstSrcChn,&pstDestChn);
	if(ret != 0){
		printf("绑定venc通道失败\n");
		return -1;
	}
	
	
	while(1){
		usleep(60);
	}
	quit = 1;
	fclose(fp);
	
	//解除通道绑定
	ret = RK_MPI_SYS_UnBind(&pstSrcChn,&pstDestChn);
	if(ret != 0){
		printf("解除通道绑定失败\n");
		return -1;
	}
	
	
	//销毁编码通道
	ret = RK_MPI_VENC_DestroyChn(0);
	if(ret != 0){
		printf("销毁编码通道失败\n");
		return -1;
	}
	
	
	//失能vi通道
	ret = RK_MPI_VI_DisableChn(0, 0);
	if(ret != 0){
		printf("失能vi通道失败\n");
		return -1;
	}
	return 0;
}


























































