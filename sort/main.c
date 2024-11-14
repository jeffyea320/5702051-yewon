#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define MAX_SIZE 10

main()
{
    int data[MAX_SIZE];
    int i;

    srand(time(0));

    for (i = 0; i < MAX_SIZE; i++)
        data[i] = rand() % 100;

    print_list(data, 10);
    // selection_sort(data, 10);
    // insertion_sort(data,10);
    bubble_sort(data, 10);
    print_list(data, 10);
}