#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int sorted[SIZE];
int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoves = 0;

void generateRandomArray(int *array)
{
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

void merge(int list[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        comparisonCount++;
        if (list[i] <= list[j])
        {
            moveCount++;
            sorted[k++] = list[i++];
        }
        else
        {
            moveCount++;
            sorted[k++] = list[j++];
        }
    }

    while (i <= mid)
    {
        moveCount++;
        sorted[k++] = list[i++];
    }
    while (j <= right)
    {
        moveCount++;
        sorted[k++] = list[j++];
    }

    for (int l = left; l <= right; l++)
    {
        moveCount++;
        list[l] = sorted[l];
    }
}

void doMergeSort(int list[], int left, int right)
{
    int mid;

    if (left < right)
    {
        mid = (left + right) / 2;
        doMergeSort(list, left, mid);
        doMergeSort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

void printArray(int *array)
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    int array[SIZE];

    for (int i; i < 20; i++)
    {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0)
        {
            printf("MergeSort\n");
            doMergeSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array);

            // isFirst++;
        }
        else
        {
            doMergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }
    printf("Average Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);
}