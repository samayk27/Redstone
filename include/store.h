#ifndef STORE_H
#define STORE_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define STORE_SIZE 1024

typedef struct {
    char *key;
    char *value;
    int in_use;
} Entry;

void store_init(void);
int store_set(const char *key, const char *value);
char *store_get(const char *key);
int store_del(const char *key);

#endif
