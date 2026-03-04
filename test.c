#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char *argv[]){
    if(argc < 2) return 1;
    
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_port = htons(0); // It isn't finished yet 
    int ver = inet_aton(argv[1], &(adr.sin_addr));

    if(ver != 1) return 1;
}
