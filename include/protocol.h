#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int argc;
    char *argv[16];
    int arglen[16];
}RESPcommand;

int resp_parse(int fd, RESPcommand *cmd);

#endif 
