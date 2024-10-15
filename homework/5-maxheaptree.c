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

HeapType *generateMaxHeapTree(int inputData[], int size); // 힙 생성
void display_heap(HeapType *h);                           // 힙 출력
void InsertMaxHeapTree(HeapType *h, element item);        // 힙에 값 삽입
element delete_max_heap(HeapType *h);                     // 최대값 삭제
void runUserInterface(HeapType *h);                       // 사용자 인터페이스 실행
void display_heap_by_level(HeapType *h);                  // 레벨별 힙 출력

// 주어진 데이터로 최대 힙을 생성하는 함수
HeapType *generateMaxHeapTree(int inputData[], int size)
{
    HeapType *root = (HeapType *)malloc(sizeof(HeapType));
    root->heap_size = 0;

    // 입력된 데이터를 사용하여 힙에 값 삽입
    for (int i = 0; i < size; i++)
    {
        InsertMaxHeapTree(root, (element){inputData[i]});
    }
    return root; // 생성된 힙 반환
}

// 힙의 모든 요소를 출력하는 함수
void display_heap(HeapType *h)
{
    for (int i = 1; i <= h->heap_size; i++)
    {
        printf("[%02d]", h->heap[i].key); // 각 요소 출력
    }
    printf("\n");
}

// 힙에 값을 삽입하는 함수
void InsertMaxHeapTree(HeapType *h, element item)
{
    int i;
    i = ++(h->heap_size);

    // 부모와 비교하여 올바른 위치 찾기
    while ((i != 1) && (item.key > h->heap[i / 2].key))
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 힙에 값을 삽입하고 힙의 상태를 출력하는 함수
void InsertMaxHeapValue(HeapType *h, element item)
{
    int i;
    int count = 0;
    i = ++(h->heap_size);

    h->heap[i] = item;
    display_heap(h);

    // 부모와 비교하여 올바른 위치 찾기
    while ((i != 1) && (h->heap[i].key > h->heap[i / 2].key))
    {
        element temp = h->heap[i];   // 현재 노드 값을 임시 저장
        h->heap[i] = h->heap[i / 2]; // 부모 노드와 교환
        h->heap[i / 2] = temp;       // 임시로 저장된 값을 부모 노드에 저장

        i /= 2;
        count++;
        display_heap(h);
    }
    printf("노드가 이동된 횟수 : %d\n", count);
}

// 최대값을 삭제하고 힙을 조정하는 함수
element delete_max_heap(HeapType *h)
{
    display_heap(h); // 삭제 전 힙 출력

    element maxItem = h->heap[1];
    h->heap[1] = h->heap[h->heap_size--];
    display_heap(h);

    int i = 1;
    int count = 0;

    // 힙의 구조를 유지하기 위해 자식 노드와 비교
    while (i * 2 <= h->heap_size)
    {
        int child = i * 2; // 왼쪽 자식 노드 인덱스

        // 오른쪽 자식 노드가 더 크면 오른쪽으로 이동
        if (child + 1 <= h->heap_size && h->heap[child].key < h->heap[child + 1].key)
        {
            child++;
        }

        // 현재 노드가 자식 노드보다 크면 종료
        if (h->heap[i].key >= h->heap[child].key)
        {
            break;
        }

        // 자식과 교환
        element temp = h->heap[i];
        h->heap[i] = h->heap[child];
        h->heap[child] = temp;

        i = child;
        count++;
        display_heap(h);
    }

    printf("노드가 이동된 횟수 : %d\n", count);
    return maxItem;
}

// 레벨별로 힙을 출력하는 함수
void display_heap_by_level(HeapType *h)
{
    if (h->heap_size == 0)
    {
        printf("Heap이 비어 있습니다.\n");
        return; // 힙이 비어있으면 종료
    }

    int level = 0;        // 현재 레벨
    int index = 1;        // 시작 인덱스
    int nodesInLevel = 1; // 현재 레벨의 노드 수
    int count = 0;        // 출력된 노드 수

    // 모든 레벨을 출력
    while (index <= h->heap_size)
    {
        printf("레벨 %d: ", level);
        for (int i = 0; i < nodesInLevel && index <= h->heap_size; i++)
        {
            printf("[%02d] ", h->heap[index].key); // 노드 값 출력
            index++;
            count++; // 출력된 노드 수 증가
        }
        printf("\n");

        level++;           // 다음 레벨로 이동
        nodesInLevel *= 2; // 레벨당 노드 수 증가
    }
}

// 사용자와의 인터페이스를 실행하는 함수
void runUserInterface(HeapType *root)
{
    char command;
    int value;

    while (1)
    {
        printf("메뉴 입력 (i: 삽입, d: 삭제, p: 출력, c: 종료): ");
        scanf(" %c", &command); // 사용자 명령어 입력

        switch (command)
        {
        case 'i':
            printf("추가할 값 입력: ");
            scanf("%d", &value);
            InsertMaxHeapValue(root, (element){value});
            break;
        case 'd':
            delete_max_heap(root);
            break;
        case 'p':
            printf("트리 레벨별 출력\n");
            display_heap_by_level(root);
            break;
        case 'c':
            printf("프로그램 종료\n");
            return;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

int main()
{
    // 테스트 데이터
    int inputData[] = {90, 89, 70, 36, 75, 63, 65, 21, 18, 15};
    int size = sizeof(inputData) / sizeof(inputData[0]); // 데이터 크기 계산

    HeapType *root = generateMaxHeapTree(inputData, size); // 최대 힙 생성
    display_heap(root);                                    // 초기 힙 출력

    runUserInterface(root); // 사용자 인터페이스 실행

    free(root); // 할당된 메모리 해제
    return 0;   // 프로그램 종료
}
