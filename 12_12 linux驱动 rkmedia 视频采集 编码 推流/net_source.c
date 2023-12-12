#include "main.h"

int video_sockfd = 0;
uint8_t send_buf[1920*1080*4]={0};
int Init_mysocket(char * ip,uint16_t port,char *server_ip,uint16_t server_port)
{
    int val = 1;//开启
    int ret = 0;
    struct sockaddr_in addr;
    struct sockaddr_in server_addr;
    int sock = socket(AF_INET,SOCK_STREAM,0);
    
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
    setsockopt(sock,SOL_SOCKET,SO_REUSEPORT,&val,sizeof(val));
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    ret = bind(sock,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        printf("绑定IP地址失败！\r\n");
        close(sock);
        return ret;
    }
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);
    server_addr.sin_family = AF_INET;
    ret = connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(ret < 0)
    {
        perror("connect");
        printf("连接服务器失败！\r\n");
        close(sock);
        return ret;
    }
    printf("连接服务器成功！\r\n");
    sleep(1);
    return sock;
}

int mysock_write(int sockfd,void * data,int size)
{
    int len = size;
    int ret = 0;
    uint8_t * p = data;
    while(1)
    {
        ret = write(sockfd,p,len);
        if(ret < 0)
        {
            perror("write");
            printf("发送数据失败！\r\n");
            return ret;
        }else if(ret == 0)
        {
            printf("服务器不在线!\r\n");
            close(sockfd);
            return 0;
        }else 
        {

            len = len - ret;
            p+=ret;
            if(len == 0)
            {
                printf("数据发送完毕！\r\n");
                break;
            }
        }

    }
    return size;
}

int mysock_read(int sockfd,void * data,int size)
{
    int len = size;
    int ret = 0;
    uint8_t * p = data;
    while(1)
    {
        ret = read(sockfd,p,len);
        if(ret < 0)
        {
            perror("read");
            printf("接受数据失败！\r\n");
            return ret;
        }else if(ret == 0)
        {
            printf("服务器不在线!\r\n");
            close(sockfd);
            return 0;
        }else 
        {

            len = len - ret;
            p+=ret;
            if(len == 0)
            {
                break;
            }
        }

    }
    return size;
}


void myargeement_packing(uint8_t * h264_data,int size)
{
    memset(send_buf,0,size + 4);
    * ((int *)send_buf) = size;
    memcpy(send_buf + 4,h264_data,size);
}

