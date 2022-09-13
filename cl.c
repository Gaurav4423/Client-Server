#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
int main(int argc, char **argv)
{
char sendline[100], recvline[100];
int sockfd;
struct sockaddr_in servaddr;
bzero(&servaddr, sizeof(servaddr));
sockfd = socket(AF_INET, SOCK_STREAM, 0);
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(22000);
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
while(1)
{
bzero(sendline,100);
bzero(recvline, 100);
fgets(sendline,100,stdin);
 int i, len, temp;  
    len = strlen(sendline); // use strlen() to get the length of str string  
      
    // use for loop to iterate the string   
    for (i = 0; i < len/2; i++)  
    {  
        // temp variable use to temporary hold the string  
        temp = sendline[i];  
        sendline[i] = sendline[len - i - 1];  
        sendline[len - i - 1] = temp;  
    }  
    printf("return :- %s", sendline);
send(sockfd, sendline, strlen(sendline),0);
recv(sockfd, recvline, 100,0);
printf("return :- %s", recvline);
}
}
