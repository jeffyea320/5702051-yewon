#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 10 // 정점 수

void printStep(int dist[], int found[])
{
    printf("Distance: ");
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
            printf("* ");
        else
            printf("%d ", dist[i]);
    }
    printf("\nFound: ");
    for (int i = 0; i < V; i++)
    {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

//===========================================================
// 인접행렬

int minDistanceMatrix(int dist[], int found[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (found[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// 인접행렬 그래프 생성
void initializeGraphMatrix(int graph[V][V])
{
    int temp[V][V] = {
        {0, 3, 0, 0, 11, 0, 0, 12, 0, 0},
        {3, 0, 8, 0, 7, 9, 0, 0, 0, 0},
        {0, 8, 0, 2, 0, 0, 0, 0, 5, 0},
        {0, 0, 2, 0, 4, 0, 0, 0, 0, 15},
        {11, 7, 0, 4, 0, 1, 13, 0, 0, 10},
        {0, 9, 0, 0, 1, 0, 18, 0, 0, 0},
        {0, 0, 0, 0, 13, 18, 0, 6, 0, 0},
        {12, 0, 0, 0, 0, 0, 6, 0, 13, 0},
        {0, 0, 5, 0, 0, 0, 0, 13, 0, 17},
        {0, 0, 0, 15, 10, 0, 0, 0, 17, 0}};

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = temp[i][j];
}

// 인접행렬 함수
void adjacencyMatrix(int graph[V][V], int src)
{
    int dist[V];
    int found[V];
    int foundOrder[V];
    int orderIndex = 0;

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        found[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V; count++)
    {
        int u = minDistanceMatrix(dist, found);
        found[u] = 1;
        foundOrder[orderIndex++] = u + 1; // 정점 1부터 시작

        printStep(dist, found);

        for (int v = 0; v < V; v++)
            if (!found[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printf("Found Order: ");
    for (int i = 0; i < orderIndex; i++)
    {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

//===================================================================
// 연결리스트

typedef struct Node
{
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct Graph
{
    Node *adjList[V];
} Graph;

Node *createNode(int vertex, int weight)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    for (int i = 0; i < V; i++)
        graph->adjList[i] = NULL;
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight)
{
    Node *newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

int minDistanceList(int dist[], int found[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (found[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

void linkedList(Graph *graph, int src)
{
    int dist[V];
    int found[V];
    int foundOrder[V];
    int orderIndex = 0;

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        found[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V; count++)
    {
        int u = minDistanceList(dist, found);
        found[u] = 1;
        foundOrder[orderIndex++] = u + 1;

        printStep(dist, found);

        Node *current = graph->adjList[u];
        while (current != NULL)
        {
            int v = current->vertex;
            int weight = current->weight;

            if (!found[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;

            current = current->next;
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < orderIndex; i++)
    {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

void initializeGraphList(Graph *graph)
{
    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 4, 11);
    addEdge(graph, 0, 7, 12);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 4, 7);
    addEdge(graph, 1, 5, 9);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 2, 8, 5);
    addEdge(graph, 3, 4, 4);
    addEdge(graph, 3, 9, 15);
    addEdge(graph, 4, 5, 1);
    addEdge(graph, 4, 6, 13);
    addEdge(graph, 4, 9, 10);
    addEdge(graph, 5, 6, 18);
    addEdge(graph, 6, 7, 6);
    addEdge(graph, 7, 8, 13);
    addEdge(graph, 8, 9, 17);
}

typedef struct MinHeapNode
{
    int vertex;
    int dist;
} MinHeapNode;

typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
} MinHeap;

MinHeapNode *newMinHeapNode(int v, int dist)
{
    MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b)
{
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap *minHeap)
{
    return minHeap->size == 0;
}

MinHeapNode *extractMin(MinHeap *minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode *root = minHeap->array[0];

    MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap *minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *minHeap, int v)
{
    return minHeap->pos[v] < minHeap->size;
}

void adjacencyList(Graph *graph, int src)
{
    int dist[V];
    int found[V] = {0};
    int foundOrder[V];
    int orderIndex = 0;

    MinHeap *minHeap = createMinHeap(V);

    for (int v = 0; v < V; v++)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        found[u] = 1;
        foundOrder[orderIndex++] = u + 1;

        printStep(dist, found);

        Node *current = graph->adjList[u];
        while (current != NULL)
        {
            int v = current->vertex;

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && current->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + current->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            current = current->next;
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < orderIndex; i++)
    {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

int main()
{
    int graph[V][V];
    initializeGraphMatrix(graph);
    printf("\n인접행렬\n");
    adjacencyMatrix(graph, 0);

    Graph *listgraph = createGraph();
    initializeGraphList(listgraph);
    printf("\n연결리스트\n");
    linkedList(listgraph, 0);

    // 동적 메모리 해제
    for (int i = 0; i < V; i++)
    {
        Node *current = listgraph->adjList[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(listgraph);

    Graph *graphmin = createGraph();
    initializeGraphList(graphmin);
    printf("\nminheap\n");
    adjacencyList(graphmin, 0);

    return 0;
}
