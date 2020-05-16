#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#define MAXBUF 256
int main()
{
    int clen;
    int ssock,csock;
    struct sockaddr_in client_addr,server_addr;
    char buf[MAXBUF];
    if((ssock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
    perror("socket error:");
    exit(1);
    }
    clen = sizeof(client_addr);
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family     =AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 
    server_addr.sin_port=htons(7758);
    if(bind(ssock,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
    perror("bind error");
    exit(1);
    }
    if(listen(ssock,8)<0){
    perror("listen error:");
    exit(1);
    }
    while(1){
    printf("ssock = %u\r\n", ssock);
    csock=accept(ssock,(struct sockaddr *)&client_addr,&clen);
    printf("csock = %u\r\n", csock);
    if(write(csock,buf, MAXBUF)<=0)
    perror("write error:");
    //close(csock);
    }
    return 0;
}
