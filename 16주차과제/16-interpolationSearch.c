#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

int comparisonCount = 0;

// 배열 생성 함수
void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 10000;
    }
}

// 배열 출력 함수
void printArray(int *array)
{
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) // 첫 20개 출력
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) // 마지막 20개 출력
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Quick Sort의 분할 과정
int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisonCount++;
        if (array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1;
}

// Quick Sort 재귀 구현
void QuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

// Binary Search 구현 및 비교 횟수 계산
int binarySearch(int array[], int size, int target)
{
    int low = 0, high = size - 1, comparisons = 0;

    while (low <= high)
    {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (array[mid] == target)
            return comparisons;

        if (array[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return comparisons; // 실패한 경우에도 비교 횟수 반환
}

// Interpolation Search 구현 및 비교 횟수 계산
int interpolationSearch(int array[], int size, int target)
{
    int low = 0, high = size - 1, comparisons = 0;

    while (low <= high && target >= array[low] && target <= array[high])
    {
        comparisons++;

        if (low == high)
        {
            if (array[low] == target)
                return comparisons;
            break;
        }

        int pos = low + ((double)(high - low) / (array[high] - array[low]) * (target - array[low]));

        if (array[pos] == target)
            return comparisons;

        if (array[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return comparisons; // 실패한 경우에도 비교 횟수 반환
}

// Binary Search 평균 비교 횟수 계산
double getAverageBinarySearchCompareCount(int array[])
{
    int totalComparisons = 0;

    for (int i = 0; i < 1000; i++)
    {
        int target = array[rand() % SIZE]; // 배열 내 랜덤 값 선택
        totalComparisons += binarySearch(array, SIZE, target);
    }

    return (double)totalComparisons / 1000;
}

// Interpolation Search 평균 비교 횟수 계산
double getAverageInterpolationSearchComparecount(int array[])
{
    int totalComparisons = 0;

    for (int i = 0; i < 1000; i++)
    {
        int target = array[rand() % SIZE]; // 배열 내 랜덤 값 선택
        totalComparisons += interpolationSearch(array, SIZE, target);
    }

    return (double)totalComparisons / 1000;
}

// 메인 함수
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);

    QuickSort(array, 0, SIZE - 1);

    printArray(array);
    printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchComparecount(array));
    return 0;
}
