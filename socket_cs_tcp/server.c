#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


int main(void)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;
    char buf[10];
    int rcv_n;

    //init socket fd -- this is a listennig socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("create server socket error!\n");
        exit(1);
    }

    //init server addr
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);    


    //bind servaddr to sockfd
    if (-1 == bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
        printf("bind sockfd error:%s(%d)\n", strerror(errno), errno);
        exit(1);
    }

    //start lisen...
    if (-1 == listen(sockfd, 10)) {
        printf("listen sockfd error:%s(%d)\n", strerror(errno), errno);
        exit(1);
    }

    //wait for requests of clients...
    printf("=======wait for client's request==========\n");
    while(1) {
        if (-1 == (connfd = accept(sockfd, (struct sockaddr*)NULL, NULL))) {
            printf("accept sockfd error!\n");
            continue;
        }
        //recevie data from clint
        rcv_n = recv(connfd, buf, 10, 0);
        //answer to client
        if (!fork()) {
            if (-1 == send(connfd, "Hello client!\n", 15, 0)) {
                printf("answer client error!\n");
                exit(1);
            }
            exit(0);
        }
        buf[rcv_n] = '\0';
        printf("recv msg from client: %s\n", buf);
        close(connfd);
	break;
    }
    
    close(sockfd);
    printf("exit system!\n");
    exit(0);
}
