#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void generateRandomData(int *array)
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

// 전체 배열을 출력하는 함수
void printArrayFull(int *array)
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 선택정렬
void doSelectionSort(int list[])
{
    int i, j, least, temp;
    int stepsSinceLastPrint = 0; // 단계 출력 제어용 변수

    for (i = 0; i < SIZE - 1; i++)
    {
        least = i;
        for (j = i + 1; j < SIZE; j++)
        {
            if (list[j] < list[least])
            {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);

        // 첫 번째 또는 20번째 간격마다 출력
        stepsSinceLastPrint++;
        if (i == 10 || stepsSinceLastPrint == 20 || i == SIZE - 2)
        {
            printf("\nSteps %d:\n", i);
            printArrayFull(list);
            stepsSinceLastPrint = 0; // 출력 후 초기화
        }
    }
}

// 삽입정렬
void doInsertionSort(int list[])
{
    int i, j, key;
    int compareCount = 0;     // 비교 횟수 저장 변수
    int totalComparisons = 0; // 20회 반복 시 총 비교 횟수 저장

    for (int run = 0; run < 20; run++) // 20번 반복 실행
    {
        // 배열을 랜덤하게 초기화
        generateRandomData(list);

        compareCount = 0; // 매번 비교 횟수 초기화

        for (i = 1; i < SIZE; i++)
        {
            key = list[i];
            j = i - 1;

            // 비교가 수행될 때마다 증가
            while (j >= 0)
            {
                compareCount++; // 비교 수행
                if (list[j] > key)
                    list[j + 1] = list[j]; // 레코드의 오른쪽 이동
                else
                    break; // 비교 후 조건이 만족하지 않으면 중단
                j--;
            }
            list[j + 1] = key;
        }

        totalComparisons += compareCount; // 각 회차의 비교 횟수를 누적
    }

    // 평균 비교 횟수 계산
    int averageComparisons = totalComparisons / 20;

    // 출력
    printf("\nInsertion Sort Compare Average: %d\n", averageComparisons);
    printf("Insertion Sort Result:\n");
    printArrayFull(list); // 배열 출력
}

// 버블정렬
void doBubbleSort(int list[])
{
    int i, j, temp;
    int swapCount = 0;  // 각 교환에서 발생하는 이동 횟수를 추적
    int totalSwaps = 0; // 총 이동 횟수

    for (int run = 0; run < 20; run++) // 20번 반복 실행
    {
        // 배열을 랜덤하게 초기화
        generateRandomData(list);

        swapCount = 0; // 각 실행에서 초기화

        for (i = SIZE - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++) // 앞뒤의 레코드를 비교한 후 교체
            {
                if (list[j] > list[j + 1])
                {
                    SWAP(list[j], list[j + 1], temp);
                    swapCount += 3; // 한 번의 SWAP에서 3회 이동
                }
            }
        }

        totalSwaps += swapCount; // 각 실행의 이동 횟수를 누적
    }

    // 평균 이동 횟수 계산
    int averageSwaps = totalSwaps / 20;

    // 출력
    printf("\nBubble Sort Move Average : %d\n", averageSwaps);
    printf("Bubble Sort Result:\n");
    printArrayFull(list); // 정렬된 배열 출력
}

int main()
{
    int randomData[SIZE];

    srand(time(NULL)); // 시드 설정: 한 번만 호출

    generateRandomData(randomData);
    doSelectionSort(randomData);

    generateRandomData(randomData);
    doInsertionSort(randomData);

    generateRandomData(randomData);
    doBubbleSort(randomData);

    return 0;
}