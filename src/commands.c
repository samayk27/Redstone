#include "../include/commands.h"

static void cmd_ping(int fd, RESPcommand *cmd) {
    if (cmd->argc == 1) {
        resp_write_simple(fd, "PONG");
    } 
    else if (cmd->argc == 2){
        resp_write_bulk(fd, cmd->argv[1], cmd->arglen[1]);
    } 
    else {
        resp_write_error(fd, "ERR wrong number of arguments for 'PING'");
    }
}

static void cmd_set(int fd, RESPcommand *cmd) {
    if(cmd->argc != 3){
        resp_write_simple_error(fd, "wrong number of arguments for 'SET' command", '-');
        return;
    }
    else if(store_set(cmd->argv[1], cmd->argv[2]) == 0){
        resp_write_simple(fd, "OK");
    }
    else{
        resp_write_simple_error(fd, "store is full", '-');
    }
}

static void cmd_get(int fd, RESPcommand *cmd) {
    if(cmd->argc != 2){
        resp_write_simple_error(fd, "wrong number of arguments for 'GET' command", '-');
        return;
    }
    else{
        char *value = store_get(cmd->argv[1]);
        if(value == NULL){
            resp_write_null(fd);
        }
        else{
            resp_write_bulk(fd, value, strlen(value));
        }
    }
}

void cmd_dispatch(int fd, RESPcommand *cmd) {
    if(strcasecmp(cmd->argv[0], "PING") == 0){
        cmd_ping(fd, cmd);
    }
    else if(strcasecmp(cmd->argv[0], "SET") == 0){
        cmd_set(fd, cmd);
    }
    else if(strcasecmp(cmd->argv[0], "GET") == 0){
        cmd_get(fd, cmd);
    }
    else{
        resp_write_error(fd, "unknown command");
    }
}
