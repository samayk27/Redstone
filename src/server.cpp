/* Personal Notes
    -socket()- creates a socket
	- bind()- bind with ip and port
	- listen()- listens for requests
	- accepts()- creates a new instance where it communicates with an individual client, while listen accepts other requests
*/
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

static void dosomething(int fd);

static int32_t one_request(int fd){
    char rbuf[4+k_max_msg];
    errno=0;
    int32_t err = read_full(fd, rbuf,4);
    if(err){
        msg(errno==0? "EOF" : "read error");
        return err;
    }
    uint32_t len =0;
    memcpy(&len, rbuf,4);
    if(len>k_max_msg){
        msg("message too long");
        return -1;
    }
    err = read_full(fd, &rbuf[4], len);
    if(err){
        msg("read error");
        return err;
    }
    printf("client says: %.*s\n", len, &rbuf[4]);
    const char reply[] = "Hello from Server";
    char wbuf[4+sizeof(reply)];
    len = (uint32_t)strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(fd, wbuf, 4+len);
}   

int main(){
    /*creating socket*/
    int fd = socket(AF_INET,SOCK_STREAM,0);
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(0);

    /*binding socket to address and port*/
    int res=bind(fd, (const struct sockaddr *)&addr, sizeof(addr));

    if(res){
        fail("bind failed");
    }

    /*listening for connections*/
    int rv = listen(fd,SOMAXCONN);

    if(rv){
        fail("listen failed");
    }

    /*accepting connections*/
    while(true){
        struct sockaddr_in client_addr= {};
        socklen_t client_addr_len = sizeof(client_addr);

        int client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if(client_fd < 0){
            continue;
        }

        while(true){
            int32_t err = one_request(client_fd);
            if(err < 0){
                break;
            }
        }
        close(client_fd);
    }
}

/*Dummy Read-Write*/
static void dosomething(int fd){
    char read_buffer[1024] = {};
    ssize_t bytes_read = read(fd, read_buffer, sizeof(read_buffer) - 1);
    if(bytes_read < 0){
        fail("read failed");
    }
    printf("Received: %s\n", read_buffer);
    char write_buffer[1024] = "Hello from server!";
    write_all(fd, write_buffer, strlen(write_buffer));
}