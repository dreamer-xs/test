#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 *
 *客户端:
 *    a. 创建一个套接子
 *	socket
 *    b. 初始化结构体
 *	sockaddr_in
 *    e. 链接服务器
 *	connect
 *    f. 读写操作
 *	read/wrte
 *
 */

#define PORT 8888

int main(void)
{
	int sockfd,ret;
	char buff[10];
	struct sockaddr_in sockaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > sockfd)
	{
		perror("socket");
	}
	
	memset(&sockaddr, 0 , sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = inet_addr("192.168.1.174");

	if(connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) != 0)
	{
		perror("connect");
		close(sockfd);
		return -1;
	}

	//printf("Success to connect %s by port: %d\n",sockaddr.sin_port.s_addr, sockaddr.sin_port);
	
 	while(1)
	{
		memset(&buff, 0, sizeof(buff));
		ret = read(sockfd, &buff,sizeof(buff));
		if(ret <= 0)
		{
			perror("read:");
			continue;
		}

		printf("Receive from server: %s \n",buff);
		sleep(1);
		
	}

	return 0;
}
	
