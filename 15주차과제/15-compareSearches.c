#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

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

int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];

    while (1) // 무한 루프, 조건을 내부에서 제어
    {

        if (low <= right && list[low] < pivot)
        {
            low++;
            compareCount++;
        }
        else if (high >= left && list[high] > pivot)
        {
            high--;
            compareCount++;
        }
        else if (low < high)
        {
            SWAP(list[low], list[high], temp);
        }
        else
        {
            break; // low >= high가 되면 루프 종료
        }
    }

    SWAP(list[left], list[high], temp);
    return high; // 피벗 위치 반환
}

void quick_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

void getQuickSortCompareCount(int *array)
{
    compareCount = 0; // 비교 횟수 초기화
    quick_sort(array, 0, SIZE - 1);
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
    // printArray(array);
    return 0;
}