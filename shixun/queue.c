#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "queue.h"

QUEUE *queue_creat(int size) {
    return llist_creat(size);
}

void queue_clear(void *ptr) {
    llist_clear(ptr);
}

void queue_push(void *ptr, void *data) {
    llist_insert_back(ptr, data);
}

int re_1(void *t1, void *t2) {
    return 1;
}

int queue_pop(void *ptr, void *data) {
    return llist_fetch(ptr, NULL, data, re_1);
}