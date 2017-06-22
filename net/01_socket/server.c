#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>


/*
 *
 *服务端:
 *    a. 创建一个套字
 *       socket
 *    b. 初始化结构体
 *       sockaddr
 *    c. 绑定
 *       bind
 *    d. 监听 设置监听队列的大小
 *       listen
 *    e. 接受客户端的连接
 *       accept
 *    f. 读写操作
 *       fread/fwrite
 *
 */


#define PORT 8888
int main(void)
{
	int sockfd, newfd,len,ret;
	char buff[10];
	struct sockaddr_in sockaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sockfd)
	{
		fprintf(stderr, "Failed to open socket\n"); 
		return 1;
	}
	
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
        
        if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) 
	{
		fprintf(stderr, "Failed to bind socket\n"); 
		close(sockfd);
		return 1;
	}

	if(listen(sockfd, 10) != 0)	
	{
		fprintf(stderr, "Failed to listen socket\n"); 
		close(sockfd);
		return 1;
	}

	fprintf(stdout, "Waiting for client ...\n");

	len = sizeof(sockaddr);
        newfd = accept(sockfd, (struct sockaddr*) &sockaddr, &len);

        if(-1 == newfd)
	{
		fprintf(stderr, "Failed to accept client\n"); 
		close(sockfd);
		return 1;
	}
	
	while(1)
	{
		memset(&buff, 0, sizeof(buff));
		strcpy(buff,"hello,svi");
		ret = write(newfd, &buff, sizeof(buff));
		if (ret <= 0)
		{
			fprintf(stderr, "Failed to send message\n"); 
			continue;
		}

		fprintf(stdout, "Send message: %s\n",buff);

		sleep(1);
	}

	close(sockfd);
	return 0;
}


