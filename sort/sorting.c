#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void print_list(int list[], int n)
{
    printf("List : ");
    for (int i = 0; i < n; i++)
        printf("[%1d]%02d ", i, list[i]);
    printf("\n");
}

void selection_sort(int list[], int n)
{
    int i, j, least, temp;

    for (int i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[least] > list[j])
                least = j;
        /* temp = list[i];
        list[i] = list[least];
        list[least] = temp; */
        SWAP(list[i], list[least], temp);
        printf("--- %d step ----", i + 1);
        print_list(list, n);
    }
}

void insertion_sort(int list[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j];
        list[j + 1] = key;
        printf("--- %d step ----", i);
        print_list(list, n);
    }
}

void bubble_sort(int list[], int n)
{
    int i, j, temp;
    int flag;

    for (i = n - 1; i > 0; i--)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (list[j] > list[j + 1])
            {
                SWAP(list[j], list[j + 1], temp);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
        printf("--- %d step ----", n - 1 - i);
        print_list(list, n);
    }
}