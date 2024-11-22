#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 100

// 0~999 사이의 랜덤 숫자를 배열에 채우는 함수
void generateRandomNumbers(int *array)
{
    sleep(1);
    srand(time(NULL));
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

// 쉘 정렬 함수: 시작 간격을 50으로 설정하여 divider로 나누어 간격을 줄임
void doShellSort(int *array, int divider, int *comparisonCount, int *moveCount)
{
    int temp, j;
    int n = ARRAY_SIZE;

    int totalComparisons = 0;
    int totalMoves = 0;

    for (int run = 0; run < 20; run++) // 20번 반복 실행
    {
        // 배열을 랜덤하게 초기화
        generateRandomNumbers(array);

        *comparisonCount = 0;
        *moveCount = 0;

        // gap을 50에서 시작하여 divider로 나누며 쉘 정렬 수행
        for (int gap = 50; gap > 0; gap /= divider)
        {
            if (run == 0) // 첫 번째 실행에서만 정렬 과정 출력
            {
                printf("Sorting with gap = %d:\n", gap);
            }

            for (int i = gap; i < n; i++)
            {
                temp = array[i];
                (*moveCount)++;
                for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                {
                    array[j] = array[j - gap];
                    (*comparisonCount)++;
                    (*moveCount)++;
                }
                array[j] = temp;
                (*moveCount)++;
            }

            if (run == 0) // 첫 번째 실행에서만 배열 일부 출력
            {
                printArrayPartial(array);
            }
        }

        totalComparisons += *comparisonCount;
        totalMoves += *moveCount;

        if (run == 0) // 첫 번째 실행에서 정렬된 배열 출력
        {
            printf("Sorted shellArray (gap = %d):\n", divider);
            printArrayFull(array);
        }
    }

    // 평균 계산 및 출력
    *comparisonCount = totalComparisons / 20;
    *moveCount = totalMoves / 20;
}

// 삽입 정렬 함수: 비교 및 이동 횟수 계산
void doInsertionSort(int *array, int *comparisonCount, int *moveCount)
{
    int temp, j;

    int totalComparisons = 0;
    int totalMoves = 0;

    for (int run = 0; run < 20; run++) // 20번 반복 실행
    {
        // 배열을 랜덤하게 초기화
        generateRandomNumbers(array);

        *comparisonCount = 0;
        *moveCount = 0;

        // 삽입 정렬 수행
        for (int i = 1; i < ARRAY_SIZE; i++)
        {
            temp = array[i];
            (*moveCount)++;
            for (j = i - 1; j >= 0 && array[j] > temp; j--)
            {
                array[j + 1] = array[j];
                (*comparisonCount)++;
                (*moveCount)++;
            }
            array[j + 1] = temp;
            (*moveCount)++;
        }

        totalComparisons += *comparisonCount;
        totalMoves += *moveCount;

        if (run == 0) // 첫 번째 실행에서만 기존 출력 수행
        {
            printf("Sorted insertionArray:\n");
            printArrayFull(array); // 정렬된 배열 전체 출력
        }
    }

    // 평균 계산 및 출력
    *comparisonCount = totalComparisons / 20;
    *moveCount = totalMoves / 20;
}

int main()
{
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // 랜덤 배열 생성
    generateRandomNumbers(array);

    // Shell Sort (n/2)
    printf("\nShell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("\nShell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("\nShell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("\nInsertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}