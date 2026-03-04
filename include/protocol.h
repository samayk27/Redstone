#ifndef PROTOCOL_H
#define PROTOCOL_H
#define RESP_MAX_ARGS 16

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct{
    int argc;
    char *argv[RESP_MAX_ARGS];
    size_t arglen[RESP_MAX_ARGS];
}RESPcommand;

int resp_parse(int fd, RESPcommand *cmd);

ssize_t resp_write_simple_error(int fd,const char *msg, char resp_0);
ssize_t resp_write_simple(int fd, const char *msg);
ssize_t resp_write_error(int fd, const char *msg);
ssize_t resp_write_bulk(int fd, const char *data, size_t len);
ssize_t resp_write_null(int fd);

#endif 
