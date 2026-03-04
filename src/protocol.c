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
    if (argc < 1 || argc > RESP_MAX_ARGS) return -1;
    cmd->argc = argc;
    for(int i=0; i<argc; i++){
        if(read(fd, &type,1)!= 1) return -1;
        if(type != '$') return -1;

        size_t arglen;
        arglen = read_number(fd);
        cmd->arglen[i] = arglen;
        cmd->argv[i] = malloc(arglen + 1);
        if(cmd->argv[i] == NULL) return -1;

        cmd->argv[i][arglen] = '\0';
        if(read(fd, cmd->argv[i], arglen) != (ssize_t)arglen) return -1;
        char crlf[2];
        read(fd, crlf, 2);
    }
    return 0;
}

ssize_t resp_write_simple_error(int fd,const char *msg, char resp_0){
    char response[1+strlen(msg)+2 + 1]; /* +1 for resp_0, +2 for \r\n, +1 for null terminator */
    response[0]=resp_0;
    strcpy(&response[1], msg);
    strcat(response, "\r\n");
    return write(fd, response, strlen(response));
}

ssize_t resp_write_simple(int fd, const char *msg){
    return resp_write_simple_error(fd,msg,'+');
}

ssize_t resp_write_error(int fd, const char *msg){
    return resp_write_simple_error(fd,msg,'-');
}

ssize_t resp_write_bulk(int fd, const char *msg, size_t msg_len){
    if(strlen(msg)!=msg_len) return -1;
    char response[6+msg_len+2 + 1]; /* +1 for null terminator */
    snprintf(response, sizeof(response), "$%zu\r\n%s\r\n", msg_len, msg);
    return write(fd, response, strlen(response));
}

ssize_t resp_write_null(int fd){
    return write(fd, "$-1\r\n", 5);
}
