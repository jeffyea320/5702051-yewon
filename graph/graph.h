#pragma once
#define MAX_VERTICES 100

typedef struct graph
{
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

extern GraphMatType *create_mat_graph();
extern void destroy_mat_graph(GraphMatType *g);
extern void init_mat_graph(GraphMatType *g);
extern void insert_vertex(GraphMatType *g, int v);
extern void insert_edge(GraphMatType *g, int start, int end);
extern void print_add_mat(GraphMatType *g);