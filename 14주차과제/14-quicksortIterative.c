#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoveCount = 0;
int isFirst = 0;

// 배열 생성 함수: 랜덤한 값으로 배열 초기화
void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

// 배열 출력 함수
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Quick Sort의 분할 과정
int partition(int array[], int low, int high)
{
    int pivot = array[high]; // 마지막 요소를 피벗으로 선택
    int i = low - 1;         // 피벗보다 작은 요소의 마지막 인덱스

    // 피벗을 기준으로 요소를 나누는 반복문
    for (int j = low; j < high; j++)
    {
        comparisonCount++; // 비교 횟수 증가
        if (array[j] <= pivot)
        {
            i++;
            // 요소 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            moveCount += 3;
        }
    }

    // 피벗을 제자리에 놓음
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    moveCount += 3;

    return i + 1; // 피벗의 최종 위치 반환
}

// 반복적 Quick Sort 구현
void doIterativeQuickSort(int array[], int low, int high)
{
    int stack[SIZE]; // 정렬할 구간을 저장하는 스택
    int top = -1;    // 스택의 꼭대기

    // 초기 구간을 스택에 추가
    stack[++top] = low;
    stack[++top] = high;

    int rounds = 0; // 출력 간격을 제어하기 위한 변수

    while (top >= 0)
    {
        // 스택에서 구간을 꺼냄
        high = stack[top--];
        low = stack[top--];

        // 현재 구간을 분할
        int pi = partition(array, low, high);

        if (isFirst == 0 && rounds % 10 == 0)
        {
            for (int i = 40; i < 60; i++)
            {
                printf("%d ", array[i]); // 40번 인덱스부터 60번까지 출력
            }
            printf("\n\n");
        }
        rounds++;

        // 분할된 왼쪽 구간을 스택에 추가
        if (pi - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // 분할된 오른쪽 구간을 스택에 추가
        if (pi + 1 < high)
        {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }

    // 첫 번째 정렬이 끝났음을 표시
    if (isFirst == 0)
    {
        isFirst++;
    }
}

int main()
{
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++)
    {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0)
        {
            printf("Quick Sort Run\n");
            doIterativeQuickSort(array, 0, SIZE - 1); // 첫 번째 정렬 수행
            printf("Result\n");
            printArray(array, SIZE); // 첫 번째 정렬 결과 출력
        }
        else
        {
            doIterativeQuickSort(array, 0, SIZE - 1); // 나머지 정렬 수행
        }

        // 비교 및 이동 횟수 누적
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 비교 및 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
