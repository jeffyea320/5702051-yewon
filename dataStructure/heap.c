#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HeapType *create_heap()
{
    return (HeapType *)malloc(sizeof(HeapType));
}

void init_heap(HeapType *h)
{
    h->heap_size = 0;
}

void destroy_heap(HeapType *h)
{
    free(h);
}

int is_empty_heap(HeapType *h)
{
    return (h->heap_size == 0);
}

int is_full_heap(HeapType *h)
{
    return (h->heap_size == (MAX_SIZE - 1));
}

void insert_heap(HeapType *h, element item)
{
    int i = h->heap_size + 1;

    while ((i < 1) && (h->heap[i / 2].key < item.key))
    {
        h->heap[i] = h->heap[i / 2];
        i = i / 2;
    }
    h->heap[i] = item;
    (h->heap_size)++;
}

element delete_heap(HeapType *h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[h->heap_size];

    (h->heap_size)--;

    for (parent = 1, child = 2; child < h->heap_size; parent = child, child = child * 2)
    {
        if ((h->heap[child].key < h->heap[child + 1].key) && child <= h->heap_size)
            child++;
        if (temp.key > h->heap[child].key)
            break;
        h->heap[parent] = h->heap[child];
    }
    h->heap[parent] = temp;

    return item;
}

element find_heap(HeapType *h)
{
    return h->heap[1];
}

void display_heap(HeapType *h)
{
    printf("Heap(%d)", h->heap_size);
    for (int i = 1; i <= h->heap_size; i++)
    {
        printf("[%02d]", h->heap[i]);
    }
    printf("\n");
}