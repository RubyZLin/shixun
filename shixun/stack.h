#ifndef STACK_H
#define STACK_H
#include "llist.h"
typedef LLIST STACK;

int re_1(void *, void *); //返回1
STACK *stack_creat(int size); //建立新栈
void stack_clear(void *ptr); //销毁栈
void stack_push(void *ptr, void *data);  //向栈中加入数据
int stack_pop(void *ptr, void *data); //从栈中弹出数据

#endif