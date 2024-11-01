#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

struct Edge
{
    int start, end, weight;
};

typedef struct GraphType
{
    int n;            // 간선의 개수
    int vertex_count; // 정점의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef struct
{
    struct Edge heap[MAX_VERTICES];
    int size;
} MinHeap;

void graph_init(GraphType *g)
{
    g->n = 0;
    g->vertex_count = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insert_edge(GraphType *g, int start, int end, int w)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;

    // 최대 정점 번호 갱신
    if (start > g->vertex_count)
        g->vertex_count = start;
    if (end > g->vertex_count)
        g->vertex_count = end;
}

void insert_min_heap(MinHeap *h, struct Edge item)
{
    int i = ++(h->size);

    while ((i != 1) && (item.weight < h->heap[i / 2].weight))
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

struct Edge delete_min_heap(MinHeap *h)
{
    int parent = 1, child = 2;
    struct Edge item, temp;

    item = h->heap[1];
    temp = h->heap[(h->size)--];

    while (child <= h->size)
    {
        if ((child < h->size) && (h->heap[child].weight > h->heap[child + 1].weight))
            child++;
        if (temp.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void GenerateGraph(GraphType *g)
{
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);

    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);

    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);

    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);

    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);

    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

void FindPrimMST(GraphType *g)
{
    int selected[MAX_VERTICES] = {0};
    MinHeap h;
    h.size = 0;

    selected[1] = 1; // 시작 정점을 1로 설정

    // 시작 정점과 연결된 모든 간선을 힙에 삽입
    for (int i = 0; i < g->n; i++)
    {
        if (g->edges[i].start == 1)
            insert_min_heap(&h, g->edges[i]);
    }

    printf("Prim MST Algorithm\n"); // 시작 정점 출력
    printf("정점 1 추가\n");        // 시작 정점 출력

    while (h.size > 0)
    {
        struct Edge edge = delete_min_heap(&h);

        if (!selected[edge.end])
        {
            printf("정점 %d 추가\n", edge.end); // 새로운 정점 추가 시 출력
            selected[edge.end] = 1;

            // 선택된 정점과 연결된 간선을 힙에 삽입
            for (int i = 0; i < g->n; i++)
            {
                if (g->edges[i].start == edge.end && !selected[g->edges[i].end])
                    insert_min_heap(&h, g->edges[i]);
            }
        }
    }
}

int main(void)
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    // 그래프를 생성하는 함수
    GenerateGraph(g);
    FindPrimMST(g); // Prim을 이용해 MST를 찾음
    free(g);
}