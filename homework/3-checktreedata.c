#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef TreeNode *element;
typedef struct
{ // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int size(QueueType *q)
{
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void PlaceNode(TreeNode *node, int direction, int data)
{
    // 먼저 노드 만들어 두기
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    // 왼쪽일 경우
    if (direction == 0)
    {
        node->left = newNode; // 노드 왼쪽이 비었으면 왼쪽에 새 노드 연결
    }
    // 오른쪽일 경우
    if (direction == 1)
    {
        node->right = newNode; // 노드 오른쪽이 비었으면 오른쪽에 새 노드 연결
    }
}

void GenerateLinkTree(TreeNode *root)
{
    int List[] = {2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};
    int direction = 0;

    PlaceNode(root, 0, List[0]);
    PlaceNode(root, 1, List[1]);
    PlaceNode(root->left, 0, List[2]);
    PlaceNode(root->left, 1, List[3]);
    PlaceNode(root->right, 0, List[4]);
    PlaceNode(root->right, 1, List[5]);
    PlaceNode(root->left->left, 0, List[6]);
    PlaceNode(root->left->left, 1, List[7]);
    PlaceNode(root->left->right, 0, List[8]);
    PlaceNode(root->left->right, 1, List[9]);
    PlaceNode(root->right->left, 0, List[10]);
    PlaceNode(root->right->left, 1, List[11]);
    PlaceNode(root->right->right, 0, List[12]);
    PlaceNode(root->right->right, 1, List[13]);
}

void GetSumOfNodes(TreeNode *root)
{
    QueueType q;
    int node_sum = 0;

    init_queue(&q); // 큐 초기화

    if (root == NULL)
        return;
    enqueue(&q, root);

    while (!is_empty(&q))
    {
        root = dequeue(&q);
        // printf(" [%d] ", root->data);
        node_sum += root->data;
        if (root->left)
            enqueue(&q, root->left);
        if (root->right)
            enqueue(&q, root->right);
    }

    printf("Sum of nodes: %d\n", node_sum);
}

void GetNumberOfNodes(TreeNode *root)
{
    QueueType q;
    int node_count = 0;

    init_queue(&q); // 큐 초기화

    if (root == NULL)
        return;
    enqueue(&q, root);
    while (!is_empty(&q))
    {
        root = dequeue(&q);
        // printf(" [%d] ", root->data);
        node_count += 1;

        if (root->left)
            enqueue(&q, root->left);
        if (root->right)
            enqueue(&q, root->right);
    }

    printf("Number of nodes: %d\n", node_count);
}

void GetHeightOfTree(TreeNode *root)
{
    if (root == NULL)
    {
        printf("Height of tree: 0\n");
        return;
    }

    QueueType q;
    init_queue(&q); // 큐 초기화
    enqueue(&q, root);

    int height = 0;

    while (!is_empty(&q))
    {
        int level_size = size(&q);

        for (int i = 0; i < level_size; i++)
        {
            root = dequeue(&q);

            if (root->left)
                enqueue(&q, root->left);
            if (root->right)
                enqueue(&q, root->right);
        }

        height++;
    }

    printf("Height of tree: %d\n", height);
}

void GetNumberOfLeafNodes(TreeNode *root)
{
    if (root == NULL)
    {
        printf("Number of leaf nodes: 0\n");
        return;
    }

    QueueType q;
    init_queue(&q); // 큐 초기화
    enqueue(&q, root);

    int leaf_count = 0;

    while (!is_empty(&q))
    {
        root = dequeue(&q);

        if (root->left == NULL && root->right == NULL)
        {
            leaf_count++;
        }

        if (root->left)
            enqueue(&q, root->left);
        if (root->right)
            enqueue(&q, root->right);
    }

    printf("Number of leaf nodes: %d\n", leaf_count);
}

int main()
{
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateLinkTree(root);

    GetSumOfNodes(root);
    GetNumberOfNodes(root);
    GetHeightOfTree(root);
    GetNumberOfLeafNodes(root);

    return 0;
}