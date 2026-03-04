/* 
*   * = Array
*   $ = string
\r\n should be consumed after reading number or string that's why we have added read for it in the code.
command =   *3\r\n
            $3\r\n
            SET\r\n
            $3\r\n
            foo\r\n
            $3\r\n
            bar\r\n
set foo bar is the result
*/

#include "../include/protocol.h"

static int read_number(int fd) {
    char buf[16];
    int i = 0;
    char c;
    while (i < (int)sizeof(buf) - 1) {
        if (read(fd, &c, 1) != 1) return -1;
        if (c == '\r') {
            read(fd, &c, 1); /* consume \n */
            break;
        }
        buf[i++] = c;
    }
    buf[i] = '\0';
    return atoi(buf);
}

int resp_parse(int fd, RESPcommand *cmd){
    char type;
    if(read(fd, &type,1)!= 1) return -1;
    if(type != '*') return -1;
    int argc;
    argc = read_number(fd);
    cmd->argc = argc;
    for(int i=0; i<argc; i++){
        if(read(fd, &type,1)!= 1) return -1;
        if(type != '$') return -1;
        int arglen;
        arglen = read_number(fd);
        cmd->arglen[i] = arglen;
        cmd->argv[i] = malloc(arglen + 1);
        cmd->argv[i][arglen] = '\0';
        if(read(fd, cmd->argv[i], arglen) != arglen) return -1;
        char crlf[2];
        read(fd, crlf, 2);
    }
    return 0;
}