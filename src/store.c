#define _POSIX_C_SOURCE 200809L //for strdup
#include "../include/store.h"

static Entry store[STORE_SIZE];

void store_init(void) {
    for(size_t i=0; i<sizeof(store)/sizeof(store[0]); i++){
        store[i].in_use = 0;
    }
}

int store_set(const char *key, const char *value) {
    for (int i = 0; i < STORE_SIZE; i++) {
        if (store[i].in_use && strcmp(store[i].key, key) == 0) {
            free(store[i].value);
            store[i].value = strdup(value);
            return 0;
        }
    }
    for (int i = 0; i < STORE_SIZE; i++) {
        if (!store[i].in_use) {
            store[i].key   = strdup(key);
            store[i].value = strdup(value);
            store[i].in_use = 1;
            return 0;
        }
    }
    return -1;
}

char *store_get(const char *key) {
    for(int i=0; i<STORE_SIZE; i++){
        if(store[i].in_use && strcmp(store[i].key, key) == 0){
            return store[i].value;
        }
    }
    return NULL;
}

int store_del(const char *key) {
    for(int i=0; i<STORE_SIZE; i++){
        if(store[i].in_use && strcmp(store[i].key, key) == 0){
            store[i].in_use = 0;
            free(store[i].key);
            free(store[i].value);
            return 0;
        }
    }
    return -1;
}