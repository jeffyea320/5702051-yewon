#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoveCount = 0;
int isFirst = 0;

// 배열 생성 함수
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
    int i = low - 1;         // 피벗보다 작은 값의 마지막 인덱스

    for (int j = low; j < high; j++)
    {
        comparisonCount++; // 비교 횟수 증가
        if (array[j] <= pivot)
        {
            i++;
            // 값 교환
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

// Quick Sort 재귀 구현
void doQuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high); // 분할 수행 및 피벗 위치 반환

        // 첫 번째 정렬의 중간 결과 출력
        if (isFirst == 0)
        {
            static int rounds = 0; // 중간 상태를 출력하기 위한 변수
            if (rounds % 10 == 0)
            {
                for (int i = 40; i < 60; i++)
                { // 인덱스 40~60 출력
                    printf("%d ", array[i]);
                }
                printf("\n\n");
            }
            rounds++;
        }

        // 재귀적으로 왼쪽과 오른쪽 부분 정렬
        doQuickSort(array, low, pi - 1);
        doQuickSort(array, pi + 1, high);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL)); // 난수 생성을 위한 시드 설정
    int array[SIZE];   // 정렬 대상 배열

    for (int i = 0; i < 20; i++)
    {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0)
        {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); // Quick Sort 수행
            printf("Result\n");
            printArray(array, SIZE); // 정렬 결과 출력
            isFirst++;               // 첫 번째 정렬 여부 변경
        }
        else
        {
            doQuickSort(array, 0, SIZE - 1); // 나머지 정렬 수행
        }

        // 비교 횟수와 이동 횟수를 누적
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 비교 횟수와 이동 횟수를 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
