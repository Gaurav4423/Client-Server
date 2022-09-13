#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void decimalToBinary(int number){
    int binaryNumber[32];
    int i = 0;
    while (number > 0) {
        binaryNumber[i] = number % 2;
        number = number / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--){
        printf("%d", binaryNumber[j]);
    }
}


void func(int connfd)
{
	char buff[MAX];
	int n;
	while(1){
		bzero(buff, MAX);

		read(connfd, buff, sizeof(buff));
		printf("From client: %s\t ", buff);
        printf("The binary of the given number is: ");
        int val=atoi(buff);
        decimalToBinary(val);
        printf("\n");
        printf("To client : ");
		bzero(buff, MAX);
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(connfd, buff, sizeof(buff));
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

int main()
{
    // int a=8;
    // decimalToBinary(a);
    // char *ip="127.0.0.1";
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));
    	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");
	func(connfd);
	close(sockfd);
    return 0;
}