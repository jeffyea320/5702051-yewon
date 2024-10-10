#pragma once
#define MAX_SIZE 100

typedef struct element
{
    int key;
} element;

typedef struct heap
{
    element heap[MAX_SIZE];
    int heap_size;
} HeapType;

extern HeapType *create_heap();
extern void init_heap(HeapType *h);
extern void destroy_heap(HeapType *h);
extern int is_empty_heap(HeapType *h);
extern int is_full_heap(HeapType *h);
extern void insert_heap(HeapType *h, element item);
extern element delete_heap(HeapType *h);
extern element find_heap(HeapType *h);
extern void display_heap(HeapType *h);