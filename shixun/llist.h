#ifndef LLIST_H
#define LLIST_H

typedef struct list_node{
    struct list_node *prev;
    struct list_node *next;
    char data[0];
}list_node;
typedef struct {
    int size;
    list_node head;
}LLIST;

list_node *llist_find_node(LLIST *ptr, void *target, int (*cmp)(void *, void *)); //查找并返回list_node指针
int llist_insert(LLIST *ptr, void *data, int type); //加入新节点

LLIST *llist_creat(int size); //建立头指针
int llist_insert_front(LLIST *ptr, void *data); //头部加入新节点
int llist_insert_back(LLIST *ptr, void *data); //尾部加入新节点
void llist_print_all(LLIST *ptr, void (*op)(void *)); //遍历输出所有内容
void *llist_find(LLIST *ptr, void *target, int (*cmp)(void *, void *)); //查找并返回data指针
int llist_fetch(LLIST *ptr, void *target, void *record, int (*cmp)(void *, void *)); //删除节点并取出
int llist_delete(LLIST *ptr, void *target, int (*cmp)(void *, void *)); //删除特定节点
int llist_clear(LLIST *ptr); //删除ptr所连接的一条链
#endif