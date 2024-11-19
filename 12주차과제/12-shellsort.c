#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 0~999 사이의 랜덤 숫자를 배열에 채우는 함수
void generateRandomNumbers(int *array)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

// 배열의 처음 20개 요소만 출력하는 함수
void printArrayPartial(int *array)
{
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("...\n");
}

// 전체 배열을 출력하는 함수
void printArrayFull(int *array)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void doShellSort(int *array, int divider, int *comparisonCount, int *moveCount)
{
    int temp, j;
    int n = ARRAY_SIZE;

    for (int gap = n / divider; gap > 0; gap /= divider)
    {
        printf("Sorting with gap = %d:\n", gap);
        for (int i = gap; i < n; i++)
        {
            temp = array[i];
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
            {
                array[j] = array[j - gap];
                        }
            array[j] = temp;
        }
        printArrayPartial(array);
    }
    printf("Sorted shellArray (gap = %d):\n", divider);
    printArrayFull(array); // 정렬된 배열 전체 출력
}

int main()
{
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // 랜덤 배열 생성
    generateRandomNumbers(array);

    // Shell Sort (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 랜덤 배열 재생성
    generateRandomNumbers(array);

    // Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 랜덤 배열 재생성
    generateRandomNumbers(array);

    return 0;
}
