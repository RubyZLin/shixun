#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#define FORWARD 1
#define BACKWARD 2

LLIST *llist_creat(int size) {
    LLIST *new = (LLIST *)malloc(sizeof(size));
    if(new == NULL) return NULL;
    new->size = size;
    new->head.prev = new->head.next = &new->head;
    return new;
}

int llist_insert(LLIST *ptr, void *data, int type) {
    list_node *newnode = (list_node *)malloc(sizeof(list_node) + ptr->size);
    if(newnode == NULL) return -1;
    memcpy(newnode->data, data, ptr->size);
    if(type == FORWARD) {
        newnode->next = ptr->head.next;
        newnode->prev = &ptr->head;
    }
    else if(type == BACKWARD) {
        newnode->next = &ptr->head;
        newnode->prev = ptr->head.prev;
    }
    newnode->next->prev = newnode;
    newnode->prev->next = newnode;
    return 0;
}

int llist_insert_front(LLIST *ptr, void *data) {
    return llist_insert(ptr, data, FORWARD);
}

int llist_insert_back(LLIST *ptr, void *data) {
    return llist_insert(ptr, data, BACKWARD);
}

void llist_print_all(LLIST *ptr, void (*op)(void *)) {
    if(ptr == NULL) {
        printf("error!\n");
        return;
    }
    list_node *p = ptr->head.next;
    while(p != &ptr->head) {
        op(p->data);
        p = p->next;
    }
}

list_node *llist_find_node(LLIST *ptr, void *target, int (*cmp)(void *, void *)) {
    if(ptr == NULL) return NULL;
    list_node *p = ptr->head.next;
    while(p != &ptr->head && cmp(p->data, target) != 1) p = p->next;
    if(p == &ptr->head) return NULL;
    else return p;
}

void *llist_find(LLIST *ptr, void *target, int (*cmp)(void *, void *)) {
    if(ptr == NULL) return NULL;
    list_node *p = llist_find_node(ptr, target, cmp);
    if(p == NULL) return NULL;
    return p->data;
}

int llist_fetch(LLIST *ptr, void *target, void *record, int (*cmp)(void *, void *)) {
    if(ptr == NULL) return 0;
    list_node *q = ptr->head.next;
    list_node *p = q->next;
    int num = 0;
    while(q != &ptr->head && cmp(q->data, target) != 1) {
        q = p;
        p = p->next;
    }
    if(q == &ptr->head) return 0;
    memcpy(record, q->data, ptr->size);
    q->next->prev = q->prev;
    q->prev->next = q->next;
    free(q);
    q = NULL;
    return 1;
}

int llist_delete(LLIST *ptr, void *target, int (*cmp)(void *, void *)) {
    if(ptr == NULL) return 0;
    list_node *q = ptr->head.next;
    list_node *p = q->next;
    int num = 0;
    while(q != &ptr->head && cmp(q->data, target) != 1) {
        q = p;
        p = p->next;
    }
    if(q == &ptr->head) return 0;
    q->next->prev = q->prev;
    q->prev->next = q->next;
    free(q);
    q = NULL;
    return 1;
}

int llist_clear(LLIST *ptr) {
    if(ptr == NULL) return 0;
    int num = 0;
    list_node *p = ptr->head.next;
    list_node *q;
    while(p != &ptr->head) {
        q = p;
        p = p->next;
        free(q);
        num++;
    }
    p = q = NULL;
    free(ptr);
    return num;
}