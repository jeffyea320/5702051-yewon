#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

typedef struct graph
{
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

GraphMatType *create_mat_graph()
{
    return (GraphMatType *)malloc(sizeof(GraphMatType));
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
        printf(stderr, "그래프: 정점의 개수 초과");
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
        printf("_______", i);
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

int main()
{
    int inputData[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    GraphMatType *g;

    g = create_mat_graph();
    init_mat_graph(g);

    insert_vertex(g, 0);
    insert_vertex(g, 1);
    insert_vertex(g, 2);
    insert_vertex(g, 3);
    insert_vertex(g, 4);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 4);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);

    print_add_mat(g);
    destroy_mat_graph(g);
}