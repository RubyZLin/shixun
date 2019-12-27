#ifndef QUEUE_H
#define QUEUE_H
#include "llist.h"
typedef LLIST QUEUE;

int re_1(void *, void *); //返回1
QUEUE *queue_creat(int size); //建立新队列
void queue_clear(void *ptr); //销毁队列
void queue_push(void *ptr, void *data);  //向队列中加入数据
int queue_pop(void *ptr, void *data); //从队列中弹出数据

#endif