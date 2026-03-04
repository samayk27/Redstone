#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>

#define k_max_msg 4096

static void fail(const char *m) {
    perror(m);
    exit(1);
}

static void msg(const char *m) {
    fprintf(stderr, "%s\n", m);
}

static int32_t read_full(int fd, void *buf, size_t count) {
    size_t total = 0;
    while (total < count) {
        ssize_t n = read(fd, (char *)buf + total, count - total);
        if (n <= 0) {
            return -1;
        }
        total += (size_t)n;
    }
    return 0;
}

static int32_t write_all(int fd, const char *buf, size_t count) {
    size_t total = 0;
    while (total < count) {
        ssize_t n = write(fd, buf + total, count - total);
        if (n <= 0) {
            return -1;
        }
        total += (size_t)n;
    }
    return 0;
}

#endif