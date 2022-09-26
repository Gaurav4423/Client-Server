#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080
int main(int argc,char const*argv[])
{
   int listen_fd,comm_fd;long valread;
   struct sockaddr_in servaddr;
   int addrlen=sizeof(servaddr);
   
   //server response
   char* server_response="HTTP/1.1 200 OK\n Content-Type: text/html\nContent-Length:72\n\n <!DOCTYPE html><html><body><h1>My First Heading</h1><p>My first paragraph.</p></body></html>";
   listen_fd=socket(AF_INET,SOCK_STREAM,0);
     //bzero(servaddr,sizeof(servaddr));
  //creating address
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=INADDR_ANY;
  servaddr.sin_port=htons(PORT);
   //memset(address.sin_zero,'\0',sizeof address.sin_zero);
  
  //binding socket with address
  bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
   listen(listen_fd,10);  
    while(1)
    {
    printf("\n+++++++ Waitning for new connection +++++++\n\n");
    comm_fd=accept(listen_fd,(struct sockaddr*)&servaddr,(socklen_t*)&addrlen);
     char buffer[30000]={0};
     valread=read(comm_fd,buffer,30000);
     printf("%s\n",buffer);
     write(comm_fd,server_response,strlen(server_response));
     printf("----------------Response sent to client----------------");
     close(comm_fd);
     }
     
 }
