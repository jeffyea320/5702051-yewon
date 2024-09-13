#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// √ ±‚»≠ «‘ºˆ
void init(LinkedStackType *s)
{
    s->top = NULL;
}
// ∞¯πÈ ªÛ≈¬ ∞À√‚ «‘ºˆ
int is_empty(LinkedStackType *s)
{
    return (s->top == NULL);
}
// ∆˜»≠ ªÛ≈¬ ∞À√‚ «‘ºˆ
int is_full(LinkedStackType *s)
{
    return 0;
}
// ª¿‘ «‘ºˆ
void push(LinkedStackType *s, element item)
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

element pop(LinkedStackType *s)
{
    StackNode *temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    free(temp);
    return data;
}

void print_stack(LinkedStackType *s)
{
    for (StackNode *p = s->top; p != NULL; p = p->link)
        printf("%d->", p->data->data); // implementation specific
    printf("NULL \n");
}
