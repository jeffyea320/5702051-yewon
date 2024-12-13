#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int compareCount = 0;
int searchCount = 0;

// 새로운 노드 생성 함수
Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// 노드 높이 반환 함수
int getHeight(Node *node)
{
    return node ? node->height : 0; // 노드가 NULL이면 높이는 0
}

// 노드 균형 계수 반환 함수
int getBalance(Node *node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// 오른쪽 회전 함수
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// 왼쪽 회전 함수
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// AVL 삽입 함수
Node *avlInsert(Node *node, int key)
{
    // 기본 BST 삽입
    if (!node)
        return createNode(key);

    if (key < node->key)
        node->left = avlInsert(node->left, key);
    else if (key > node->key)
        node->right = avlInsert(node->right, key);
    else
        return node;

    // 노드의 높이 업데이트
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    // 균형 계수 계산
    int balance = getBalance(node);

    // 불균형 케이스 처리
    if (balance > 1 && key < node->left->key) // 왼쪽-왼쪽 케이스
        return rightRotate(node);

    if (balance < -1 && key > node->right->key) // 오른쪽-오른쪽 케이스
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) // 왼쪽-오른쪽 케이스
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) // 오른쪽-왼쪽 케이스
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// BST 삽입 함수
Node *bstInsert(Node *node, int key)
{
    if (!node)
        return createNode(key);

    if (key < node->key)
        node->left = bstInsert(node->left, key);
    else if (key > node->key)
        node->right = bstInsert(node->right, key);

    return node;
}

// 탐색 함수
int search(Node *node, int key)
{
    int count = 0;
    while (node)
    {
        count++;
        if (key == node->key)
            return count;
        else if (key < node->key)
            node = node->left; // 왼쪽 서브트리 탐색
        else
            node = node->right; // 오른쪽 서브트리 탐색
    }
    return count;
}

// 노드 삭제 함수
Node *deleteNode(Node *root, int key)
{
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        // 하나 또는 없는 자식 노드 처리
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        // 두 자식 노드가 있는 경우
        Node *temp = root->right;
        while (temp->left)
            temp = temp->left; // 오른쪽 서브트리에서 최소값 찾기

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// 트리 메모리 해제
void freeTree(Node *root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void doAVLBatch(Node **root)
{
    for (int i = 0; i < 2000; i++)
    {
        int op = rand() % 3;     // (0: 삽입, 1: 삭제, 2: 탐색)
        int num = rand() % 1000; // 0~999 범위의 랜덤 키 생성
        if (op == 0)
        {
            *root = avlInsert(*root, num);
        }
        else if (op == 1)
        {
            *root = deleteNode(*root, num);
        }
        else
        {
            compareCount += search(*root, num);
            searchCount++;
        }
    }
}

void doBinaryBatch(Node **root)
{
    for (int i = 0; i < 2000; i++)
    {
        int op = rand() % 3;     // (0: 삽입, 1: 삭제, 2: 탐색)
        int num = rand() % 1000; // 0~999 범위의 랜덤 키 생성
        if (op == 0)
        {
            *root = bstInsert(*root, num);
        }
        else if (op == 1)
        {
            *root = deleteNode(*root, num);
        }
        else
        {
            compareCount += search(*root, num);
            searchCount++;
        }
    }
}

int main(int argc, char *argv[])
{
    Node *root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // AVL 트리 배치 작업
    compareCount = searchCount = 0;
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
    printf("average AVL compare count: %.2f\n", allCount);

    // AVL 트리 데이터 해제
    freeTree(root);
    root = NULL;

    // BST 배치 작업
    compareCount = searchCount = 0;
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}
