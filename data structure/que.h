#pragma once
#include "levelTree.h"
#define MAX_QUEUE_SIZE 100

typedef TreeNode *element;
typedef struct
{ // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

extern void init_queue(QueueType *s);
extern int is_empty(QueueType *s);
extern int is_full(QueueType *s);
extern void enqueue(QueueType *s, element item);
extern element dequeue(QueueType *s);
