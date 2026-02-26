#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include "../include/methods.h"

struct sockaddr_in addr = {};

int main(){
    /*creating socket*/
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0){
        fail("socket failed");
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); /*INADDR_LOOPBACK is for localhost (127.0.0.1)*/

    /*connecting to server*/
    int res=connect(fd, (const struct sockaddr *)&addr, sizeof(addr));

    if(res){
        fail("connect failed");
    }

    char write_buffer[1024] = "Hello from client!";
    write(fd, write_buffer, sizeof(write_buffer));

    char read_buffer[1024] = {};
    ssize_t bytes_read = read(fd, read_buffer, sizeof(read_buffer) - 1);
    if(bytes_read < 0){
        fail("read failed");
    }
    printf("Received: %s\n", read_buffer);
    close(fd);
}