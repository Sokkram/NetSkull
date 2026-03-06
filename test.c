#define SIZE 64
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char *argv[]){
    if(argc != 2) return 1;
    int sock;
    char buffer[SIZE];
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    int ver = inet_aton(argv[1], &(adr.sin_addr));

    if(ver != 1) return 1;
    for (unsigned short i=1; i<65535; i++){
        sock = socket(PF_INET,SOCK_STREAM,0);
        adr.sin_port = htons(i);
        if(connect(sock,(struct sockaddr *)&adr, sizeof(struct sockaddr_in))==0)
            printf("Open TCP port number: %hu\n",i);
        else{
            sock = socket(PF_INET, SOCK_DGRAM,0);
            if(sendto(sock,buffer, strlen(buffer),32,(struct sockaddr *)&adr, sizeof(struct sockaddr_in))>=0)
                printf("Open UDP port number: %hu\n",i);
        }
        close(sock);
            
    }
}
