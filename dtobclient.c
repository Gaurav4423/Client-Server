#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/socket.h>
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


void func(int sockfd)
{
	char buff[MAX];
	int n;
	while(1) {
		bzero(buff, sizeof(buff));
		printf("Enter the decimal : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s\t", buff);
		int value;
		printf("Binary value of the given number is: ");
		value=atoi(buff);
		decimalToBinary(value);
		printf("\n");
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main()
{
	char *I_P="127.0.0.1";
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(I_P);
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	func(sockfd);
	close(sockfd);
}