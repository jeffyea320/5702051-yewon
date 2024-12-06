#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0;

// 0~999 사이의 랜덤 숫자를 배열에 채우는 함수
void generateRandomArray(int *array)
{
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }
}

void printArray(int *array)
{
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

double getAverageLinearSearchCompareCount(int *array)
{
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++)
    {
        int randomIndex = rand() % SIZE;
        int target = array[randomIndex];

        int comparisons = 0;
        for (int j = 0; j < SIZE; j++)
        {
            comparisons++;
            if (array[j] == target)
            {
                break;
            }
        }
        totalComparisons += comparisons;
    }

    return (double)totalComparisons / 100;
}

// Quick Sort의 분할 과정
int partition(int array[], int low, int high)
{
    int pivot = array[high]; // 마지막 요소를 피벗으로 선택
    int i = low - 1;         // 피벗보다 작은 값의 마지막 인덱스

    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            compareCount++; // 비교 횟수 증가
            i++;
            // 값 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // 피벗을 제자리에 놓음
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1; // 피벗의 최종 위치 반환
}

// Quick Sort 재귀 구현
void doQuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high); // 분할 수행 및 피벗 위치 반환

        // 재귀적으로 왼쪽과 오른쪽 부분 정렬
        doQuickSort(array, low, pi - 1);
        doQuickSort(array, pi + 1, high);
    }
}

void getQuickSortCompareCount(int *array)
{
    compareCount = 0; // 비교 횟수 초기화
    doQuickSort(array, 0, SIZE - 1);
}

double getAverageBinarySearchCompareCount(int *array)
{
    int totalComparisons = 0;

    for (int i = 0; i < 100; i++)
    {
        int left = 0, right = SIZE - 1;
        int randomIndex = rand() % SIZE;
        int target = array[randomIndex];
        int comparisons = 0;

        while (left <= right)
        {
            comparisons++;
            int mid = (left + right) / 2;

            if (array[mid] == target)
            {
                break;
            }
            else if (array[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        totalComparisons += comparisons;
    }

    return (double)totalComparisons / 100;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);

    printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));

    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    printf("Average Binary Search Compare Count: %.2f\n\n", getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}