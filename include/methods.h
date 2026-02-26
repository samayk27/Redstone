#include<err.h>

static void fail(const char* msg){
    perror(msg);
    exit(1);
}