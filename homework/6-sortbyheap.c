#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct element
{
    int key;
} element;

typedef struct heap
{
    element heap[MAX_SIZE];
    int heap_size;
} HeapType;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙을 재정렬하는 함수
void resortHeap(int inputData[], int n, int i)
{
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // 왼쪽 자식이 더 큰 경우
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식이 더 큰 경우
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // 가장 큰 값이 부모가 아닌 경우, 교환 후 재정렬
    if (largest != i)
    {
        swap(&inputData[i], &inputData[largest]);

        // 재귀적으로 힙을 재정렬
        resortHeap(inputData, n, largest);
    }
}

// 힙에 값을 하나씩 추가하고 그 상태를 출력하는 함수
void insertIntoHeap(int inputData[], int n)
{
    int i = n - 1; // 새로 추가된 원소의 인덱스
    int parent = (i - 1) / 2;

    // 새로운 값을 힙의 올바른 위치에 배치
    while (i > 0 && inputData[i] > inputData[parent])
    {
        swap(&inputData[i], &inputData[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }

    // 값 추가 후 상태 출력
    for (int j = 0; j < n; j++)
    {
        printf("%d ", inputData[j]);
    }
    printf("\n");
}

// 배열을 최대 힙으로 변환하는 함수
void BuildMaxHeap(int inputData[], int n)
{
    // 마지막 부모 노드부터 시작해서 최대 힙을 구성
    for (int i = 0; i < n; i++)
    {
        insertIntoHeap(inputData, i + 1);
    }
}

void BuildMaxHeapAndSort(int inputData[], int n)
{
    // max heap 생성하는 함수
    BuildMaxHeap(inputData, n);

    // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = n - 1; i > 0; i--)
    {
        swap(&inputData[0], &inputData[i]); // 최대값(루트)과 마지막 요소 교환
        resortHeap(inputData, i, 0);        // 교환된 힙에서 루트 재정렬

        // 재정렬 후 상태 출력
        for (int j = 0; j < i; j++)
        {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main()
{
    int inputData[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};
    int size = sizeof(inputData) / sizeof(inputData[0]);
    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", inputData[i]);
    }
    printf("\n");
    return 0;
}