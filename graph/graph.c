#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

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
