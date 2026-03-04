#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/methods.h"

static int32_t query(int fd, const char *text) {
    uint32_t len = (uint32_t)strlen(text);
    if (len > k_max_msg) {
        return -1;
    }

    char wbuf[4 + k_max_msg];
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], text, len);

    int32_t err = write_all(fd, wbuf, 4 + len);
    if (err) {
        return err;
    }

    char rbuf[4 + k_max_msg];
    errno = 0;
    err = read_full(fd, rbuf, 4);
    if (err) {
        msg(errno == 0 ? "EOF" : "read error");
        return err;
    }

    memcpy(&len, rbuf, 4);
    if (len > k_max_msg) {
        msg("message too long");
        return -1;
    }

    err = read_full(fd, &rbuf[4], len);
    if (err) {
        msg("read error");
        return err;
    }

    printf("server says: %.*s\n", len, &rbuf[4]);
    return 0;
}

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        fail("socket failed");
    }

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(6379);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); /* 127.0.0.1 */

    int res = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (res) {
        fail("connect failed");
    }

    int32_t err;
    err = query(fd, "Hello from client!");
    if (err) goto DONE;
    err = query(fd, "How are you?");
    if (err) goto DONE;

DONE:
    close(fd);
    return 0;
}
