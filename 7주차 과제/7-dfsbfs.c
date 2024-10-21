#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct graph
{
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

// 큐 구조체 정의
typedef struct
{
    int queue[MAX_VERTICES];
    int front, rear;
} Queue;

void init_queue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

int is_empty_queue(Queue *q)
{
    return (q->front == q->rear);
}

void enqueue(Queue *q, int v)
{
    q->queue[(q->rear)++] = v;
}

int dequeue(Queue *q)
{
    return q->queue[(q->front)++];
}

// 스택 구조체 정의
typedef struct
{
    int stack[MAX_VERTICES];
    int top;
} Stack;

void init_stack(Stack *s)
{
    s->top = -1;
}

int is_empty(Stack *s)
{
    return (s->top == -1);
}

void push(Stack *s, int v)
{
    s->stack[++(s->top)] = v;
}

int pop(Stack *s)
{
    return s->stack[(s->top)--];
}

// visited 배열을 초기화하는 함수
void reset_visited()
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        visited[i] = FALSE;
    }
}

// 깊이 우선 탐색
void dfs_mat_iterative(GraphMatType *g, int v, int search)
{
    Stack s;
    init_stack(&s);
    int visited_count = 0;
    int found = FALSE;

    push(&s, v);

    while (!is_empty(&s))
    {
        int current = pop(&s);

        if (!visited[current])
        { // 중복 방문 방지
            visited[current] = TRUE;
            printf("%d ", current); // 방문한 노드 출력
            visited_count++;

            if (current == search)
            {
                found = TRUE;
                break;
            }

            for (int w = g->n - 1; w >= 0; w--)
            {
                if (g->adj_mat[current][w] && !visited[w])
                {
                    push(&s, w);
                }
            }
        }
    }

    if (found)
        printf("\n탐색 성공: %d\n", search);
    else
        printf("\n탐색 실패: 존재하지 않는 값\n");

    printf("방문한 노드의 수: %d\n", visited_count);
}

// 너비 우선 탐색 함수
void bfs_mat(GraphMatType *g, int v, int search)
{
    Queue q;
    init_queue(&q);
    int visited_count = 0;
    int found = FALSE;

    enqueue(&q, v);

    while (!is_empty_queue(&q))
    {
        int current = dequeue(&q);

        if (!visited[current])
        {
            visited[current] = TRUE;
            printf("%d ", current); // 방문한 노드 출력
            visited_count++;

            if (current == search)
            {
                found = TRUE;
                break;
            }

            for (int w = 0; w < g->n; w++)
            {
                if (g->adj_mat[current][w] && !visited[w])
                {
                    enqueue(&q, w);
                }
            }
        }
    }

    if (found)
        printf("\n탐색 성공: %d\n", search);
    else
        printf("\n탐색 실패: 존재하지 않는 값\n");

    printf("방문한 노드의 수: %d\n", visited_count);
}

void destroy_mat_graph(GraphMatType *g)
{
    free(g);
}

void init_mat_graph(GraphMatType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}

// 정점 삽입 연산
void insert_vertex(GraphMatType *g, int v)
{
    if (((g->n) + 1) > MAX_VERTICES)
    {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    (g->n)++;
}

// 간선 삽입 연산
void insert_edge(GraphMatType *g, int start, int end)
{
    if (start >= g->n || end >= g->n)
    {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// 그래프 출력 함수
void print_adj_mat(GraphMatType *g)
{
    printf("     ");
    for (int i = 0; i < g->n; i++)
    {
        printf(" %02d ", i);
    }
    printf("\n_____");
    for (int i = 0; i < g->n; i++)
    {
        printf("_______");
    }
    printf("\n");
    for (int i = 0; i < g->n; i++)
    {
        printf(" %02d: ", i);
        for (int j = 0; j < g->n; j++)
            printf(" %02d ", g->adj_mat[i][j]);
        printf("\n");
    }
}

// 간선들이 추가된 그래프를 생성하는 함수
GraphMatType *generateMatType()
{
    GraphMatType *g = (GraphMatType *)malloc(sizeof(GraphMatType)); // 그래프 생성
    init_mat_graph(g);                                              // 그래프 초기화

    // 정점 추가
    for (int i = 0; i < 11; i++) // 0 ~ 10 노드
        insert_vertex(g, i);

    // 간선 추가
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 4);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 1, 5);
    insert_edge(g, 1, 7);
    insert_edge(g, 1, 10);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 1);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 6, 9);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);
    insert_edge(g, 8, 10);

    return g;
}

// 사용자와의 인터페이스를 실행하는 함수
void runUserInterface(GraphMatType *g)
{
    char command;
    int start, search;

    while (1)
    {
        printf("메뉴 입력 (1: 깊이 우선 탐색, 2: 너비 우선 탐색, 3: 종료): ");
        scanf(" %c", &command); // 사용자 명령어 입력

        switch (command)
        {
        case '1':
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &search);
            reset_visited();                     // 방문 기록 초기화
            dfs_mat_iterative(g, start, search); // 깊이 우선 탐색 수행
            break;
        case '2':
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &search);
            reset_visited();           // 방문 기록 초기화
            bfs_mat(g, start, search); // 너비 우선 탐색 수행
            break;
        case '3':
            printf("프로그램 종료\n");
            return;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

int main()
{
    GraphMatType *g = generateMatType(); // 그래프 생성
    runUserInterface(g);                 // 사용자 인터페이스 실행
    destroy_mat_graph(g);                // 그래프 메모리 해제
}
