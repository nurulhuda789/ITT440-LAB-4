#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> 
#define MAX 80  
#define SA struct sockaddr 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int q; 
    for (;;) 
    {
        bzero(buff, sizeof(buff)); 
        puts("WELCOME TO FRIEND CHAT !!");
        puts("Enter Your Message : "); 
        q = 0; 
        while ((buff[q++] = getchar()) != '\n'); 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) 
  	{ 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    	bzero(&servaddr, sizeof(servaddr)); 
  
     
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("192.168.43.81"); 
    servaddr.sin_port = htons( 8888 ); 
  
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed..\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    
    func(sockfd);  
    close(sockfd); 
} 


