#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
int main()
{
int listen_fd, comm_fd;
char str[100];
char rep[100];
struct sockaddr_in servaddr;
bzero(&servaddr, sizeof(servaddr));
listen_fd = socket(AF_INET, SOCK_STREAM, 0);
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
listen(listen_fd, 10);
comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
while(1)
{

bzero(str,100);
bzero(rep,100);
recv(comm_fd, str, 100, 0);
printf("Echoing back; %s", str);
fgets(rep,100,stdin);
send(comm_fd, rep, strlen(rep),100);
}
}
