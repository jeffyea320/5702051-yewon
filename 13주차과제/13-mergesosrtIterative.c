#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int sorted[SIZE]; // 임시 배열

int comparisonCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoves = 0;
int rounds = 0;  // 정렬 과정 추적
int isFirst = 0; // 정렬 과정 한번만 출력하기 위한 변수

// 배열에 랜덤 값 생성
void generateRandomArray(int *array)
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

// 배열 일부분 출력
void printArrayState(int *array)
{
    // 앞에 10개 출력
    for (int i = 0; i < 10; i++)
        printf("%3d ", array[i]);
    printf("| ");

    // 중간 10개 출력
    for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// 병합함수
void merge(int list[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        comparisonCount++;      // 비교 횟수 증가
        if (list[i] <= list[j]) // 왼쪽 배열 원소가 더 작거나 같으면
        {
            moveCount++;             // 이동 횟수 증가
            sorted[k++] = list[i++]; // 왼쪽 배열 원소를 임시 배열에 복사
        }
        else
        {
            moveCount++;             // 이동 횟수 증가
            sorted[k++] = list[j++]; // 오른쪽 배열 원소를 임시 배열에 복사
        }
    }

    // 왼쪽 배열의 남은 원소를 임시 배열에 복사
    while (i <= mid)
    {
        moveCount++; // 이동 횟수 증가
        sorted[k++] = list[i++];
    }

    // 오른쪽 배열의 남은 원소를 임시 배열에 복사
    while (j <= right)
    {
        moveCount++; // 이동 횟수 증가
        sorted[k++] = list[j++];
    }

    // 원래 배열에 옮기기
    for (int l = left; l <= right; l++)
    {
        moveCount++; // 이동 횟수 증가
        list[l] = sorted[l];
    }

    // 정렬 과정 출력 (10회마다 한번)
    rounds++;
    if (rounds % 10 == 0 && isFirst == 0)
    {
        printArrayState(list);
    }
}

// 반복적인 병합 정렬 함수 (스택 사용)
void doMergeSortIterative(int list[], int left, int right)
{
    // 스택을 이용하여 반복적으로 병합 정렬 수행
    int stack[right - left + 1];
    int top = -1;

    // 첫 번째 구간을 스택에 푸시
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0)
    {
        // 스택에서 왼쪽과 오른쪽 인덱스 꺼내기
        right = stack[top--];
        left = stack[top--];

        if (left < right)
        {
            int mid = (left + right) / 2;

            // 중간 인덱스를 기준으로 왼쪽 구간과 오른쪽 구간을 스택에 푸시
            stack[++top] = left;
            stack[++top] = mid;

            stack[++top] = mid + 1;
            stack[++top] = right;

            // 병합 정렬 수행
            merge(list, left, mid, right);
        }
    }
}

// 최종 정렬된 배열 출력
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
    srand(time(NULL));

    // 반복적인 방법으로 수행
    totalComparisons = 0;
    totalMoves = 0;
    isFirst = 0; // 반복적인 방법에서 다시 출력

    for (int i = 0; i < 20; i++)
    {
        generateRandomArray(array); // 매번 새로운 랜덤 배열 생성
        comparisonCount = 0;        // 비교 횟수 초기화
        moveCount = 0;              // 이동 횟수 초기화

        if (i == 0) // 첫 번째 정렬에서만 출력
        {
            printf("MergeSort (Iterative)\n");
            doMergeSortIterative(array, 0, SIZE - 1); // 반복적인 병합 정렬

            printf("Result\n");
            printArray(array);
            isFirst++; // 첫 번째 출력 완료 후 isFirst 증가(다음번 출력 x)
        }
        else
        {
            doMergeSortIterative(array, 0, SIZE - 1); // 추가적인 정렬 수행
        }

        // 비교 및 이동 횟수 합산
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // 20번 정렬 후 평균 비교 및 이동 횟수 출력
    printf("Average Comparisons (Iterative): %.2f\n", totalComparisons / 20.0);
    printf("Average Moves (Iterative): %.2f\n", totalMoves / 20.0);

    return 0;
}
