#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "stack.h"

STACK *stack_creat(int size) {
    return llist_creat(size);
}

void stack_clear(void *ptr) {
    llist_clear(ptr);
}

void stack_push(void *ptr, void *data) {
    llist_insert_front(ptr, data);
}

int re_1(void *t1, void *t2) {
    return 1;
}

int stack_pop(void *ptr, void *data) {
    return llist_fetch(ptr, NULL, data, re_1);
}