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
    int ssock;
    int clen;
    struct sockaddr_in client_addr,server_addr;
    char buf[MAXBUF];
    if((ssock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0){
    perror("socket error:");
    exit(1);
    }
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(7758);
    if(bind(ssock,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
    perror("bind error:");
    exit(1);
    }
    clen=sizeof(client_addr);
while(1)
{
    recvfrom(ssock,(void *)buf,MAXBUF,0,(struct sockaddr*)&client_addr,&clen);
    printf("ssock = %d\r\n", ssock);
    strcpy(buf,"I am 7758 server");
    sendto(ssock,(void *)buf,MAXBUF,0,(struct sockaddr*)&client_addr ,sizeof(client_addr));
#if 0
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    client_addr.sin_port=htons(7759);

    sendto(ssock,(void *)buf,MAXBUF,0,(struct sockaddr*)&client_addr ,sizeof(client_addr));
#endif
}
    close(ssock);
    return 0;
}
