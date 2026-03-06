#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    if(argc != 2) return 1;
    int sock;
    struct sockaddr_in adr;
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    int ver = inet_aton(argv[1], &(adr.sin_addr));
    struct timeval t;
    t.tv_sec = 0;
    t.tv_usec = 200000;
    if(ver != 1) return 1;
    for (int i=1; i<1024; i++){
        sock = socket(AF_INET,SOCK_STREAM,0);
        if(sock == -1){
            printf("Error number: %d\n", errno);
            printf("Error message: %s\n", strerror(errno));
            continue;
        }else{
            adr.sin_port = htons(i);
            int result = setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO, &t,sizeof(t));
            if(result != 0){
                close(sock);
                continue;
            } 
            else{
               if(connect(sock,(struct sockaddr *)&adr, sizeof(struct sockaddr_in))==0)
                printf("Open TCP port number: %d\n",i);
            }
        }
        close(sock);        
    }
    printf("Scan finished\n");
    return 0;
}



/*
sock = socket(PF_INET, SOCK_DGRAM,0);
if(sendto(sock,buffer, strlen(buffer),32,(struct sockaddr *)&adr, sizeof(struct sockaddr_in))>=0)
    printf("Open UDP port number: %hu\n",i);
*/