#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
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