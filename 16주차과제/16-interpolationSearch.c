#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void generateRandomArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 10000;
    }
}

// 배열의 처음 20개와 마지막 20개의 원소를 출력
void printArray(int *array)
{
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// Quick Sort partition
int partition(int array[], int low, int high)
{
    int pivot = array[high]; // 마지막 원소를 피벗으로 선택
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
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

// Quick Sort
void QuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

double getAverageBinarySearchCompareCount(int *array)
{
    int totalComparisons = 0;

    for (int i = 0; i < 1000; i++)
    {
        int left = 0, right = SIZE - 1;
        int randomIndex = rand() % SIZE;
        int target = array[randomIndex];
        int comparisons = 0;

        while (left <= right)
        {

            int mid = (left + right) / 2;

            if (array[mid] == target)
            {
                comparisons++;
                break;
            }
            else if (array[mid] < target)
            {
                comparisons++;
                left = mid + 1;
            }
            else
            {
                comparisons++;
                right = mid - 1;
            }
        }
        totalComparisons += comparisons;
    }

    return (double)totalComparisons / 1000;
}

double getAverageInterpolationSearchComparecount(int array[])
{
    int totalComparisons = 0;

    for (int i = 0; i < 1000; i++)
    {
        int target = array[rand() % SIZE];
        int low = 0, high = SIZE - 1, comparisons = 0;

        // 보간 탐색
        while (low <= high && target >= array[low] && target <= array[high])
        {
            comparisons++;

            if (low == high)
            {
                comparisons++;
                if (array[low] == target)
                    break;
                break;
            }

            // 보간 탐색의 위치 계산
            int pos = low + ((double)(high - low) / (array[high] - array[low]) * (target - array[low]));

            comparisons++;
            if (array[pos] == target)
                break;

            comparisons++;
            if (array[pos] < target)
            {
                low = pos + 1;
            }
            else
            {
                high = pos - 1;
            }
        }

        totalComparisons += comparisons; // 비교 횟수 누적
    }

    return (double)totalComparisons / 1000; // 평균 비교 횟수 계산
}

// 메인 함수
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);

    QuickSort(array, 0, SIZE - 1);

    printArray(array);
    printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));               // 이진 탐색 평균 비교 횟수 출력
    printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchComparecount(array)); // 보간 탐색 평균 비교 횟수 출력
    return 0;
}
