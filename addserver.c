#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
int main()
{
	int listen_fd, comm_fd;
	char str[100];
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(22000);
	bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listen_fd, 10);
	
	while(1){
		comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
		bzero(str, 100);
		recv(comm_fd, str, 100, 0);
		int num = atoi(str);
		
		bzero(str, 100);
		recv(comm_fd, str, 100, 0);
		int num1 = atoi(str);
		
		int sum = num+num1;
	//	printf("Echoing back - %s", str);
		sprintf(str,"%d", sum);
		send(comm_fd, str, strlen(str), 0);
		close(comm_fd);
	}
}
