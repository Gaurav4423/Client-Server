#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
int main()
{
char str[100],str1[100],z[200];
int listen_fd, comm_fd,n;
struct sockaddr_in servaddr;
listen_fd = socket(AF_INET, SOCK_STREAM, 0);
bzero( &servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(22000);
bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen(listen_fd, 10);

while(1)
{
comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
bzero( str, 100);
recv(comm_fd,str,100,0);
strcpy(z,str);
recv(comm_fd,str1,100,0);
if(strcmp(z,str1)==0)
	send(comm_fd,"Strings are equal",100,0);
else
	send(comm_fd,"Strings are not equal",100,0);

close(comm_fd);

}
}
