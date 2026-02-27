#include<err.h>

const size_t k_max_msg = 4096;

static void fail(const char* msg){
    perror(msg);
    exit(1);
}

static void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

static int32_t read_full(int fd, void *buf, size_t count){
    size_t total_read = 0;
    while(total_read < count){
        ssize_t bytes_read = read(fd, (char*)buf + total_read, count - total_read);
        if(bytes_read <= 0){
            return -1;
        }
        total_read += bytes_read;
    }
    return 0;
}

static int32_t write_all(int fd, const char* buf, size_t count){
    size_t total_written=0;
    while(total_written<count){
        ssize_t bytes_written = write(fd, buf + total_written, count - total_written);
        if(bytes_written <= 0){
            return -1;
        }
        total_written += bytes_written;
    }
    return 0;
}