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

static int32_t one_request(int fd) {
    char rbuf[4 + k_max_msg];
    errno = 0;
    int32_t err = read_full(fd, rbuf, 4);
    if (err) {
        msg(errno == 0 ? "EOF" : "read error");
        return err;
    }

    uint32_t len = 0;
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

    printf("client says: %.*s\n", len, &rbuf[4]);

    const char reply[] = "Hello from Server";
    char wbuf[4 + sizeof(reply)];
    len = (uint32_t)strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(fd, wbuf, 4 + len);
}

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(6379);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int res = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (res) {
        fail("bind failed");
    }

    int rv = listen(fd, SOMAXCONN);
    if (rv) {
        fail("listen failed");
    }

    printf("Redstone listening on port 6379\n");

    while (1) {
        struct sockaddr_in client_addr = {0};
        socklen_t client_addr_len = sizeof(client_addr);

        int client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            continue;
        }

        while (1) {
            int32_t err = one_request(client_fd);
            if (err < 0) {
                break;
            }
        }
        close(client_fd);
    }

    return 0;
}
