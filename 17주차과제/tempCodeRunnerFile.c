#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int key;
    struct Node *left, *right;
    int height;
} Node;

int compareCount = 0;
int searchCount = 0;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // For AVL tree
    return newNode;
}

// Utility function to get the height of a node
int getHeight(Node *node)
{
    return node ? node->height : 0;
}

// Utility function to calculate balance factor
int getBalance(Node *node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right rotate
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

// Left rotate
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

// AVL insertion
Node *avlInsert(Node *node, int key)
{
    if (!node)
        return createNode(key);

    if (key < node->key)
        node->left = avlInsert(node->left, key);
    else if (key > node->key)
        node->right = avlInsert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// BST insertion
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

// AVL and BST search
int search(Node *node, int key)
{
    int count = 0;
    while (node)
    {
        if (key == node->key)
        {
            count++;
            return count;
        }
        else if (key < node->key)
        {
            count++;
            node = node->left;
        }
        else
        {
            count++;

            node = node->right;
        }
    }
    return count;
}

// AVL and BST delete
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
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        Node *temp = root->right;
        while (temp->left)
            temp = temp->left;

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

void freeTree(Node *root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void doAVLBatch(Node *root)
{
    for (int i = 0; i < 2000; i++)
    {
        int op = rand() % 3;
        int num = rand() % 1000;
        if (op == 0)
        {
            root = avlInsert(root, num);
        }
        else if (op == 1)
        {
            root = deleteNode(root, num);
        }
        else
        {
            compareCount += search(root, num);
            searchCount++;
        }
    }
}

void doBinaryBatch(Node *root)
{
    for (int i = 0; i < 2000; i++)
    {
        int op = rand() % 3;
        int num = rand() % 1000;
        if (op == 0)
        {
            root = bstInsert(root, num);
        }
        else if (op == 1)
        {
            root = deleteNode(root, num);
        }
        else
        {
            compareCount += search(root, num);
            searchCount++;
        }
    }
}
int main(int argc, char *argv[])
{
    Node *root = NULL;
    srand(time(NULL));
    float allCount = 0.0;
    // 과제에서 제시된 AVL 에 대한 2000 회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);
    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;
    // 과제에서 제시된 Binary Search Tree Batch 를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);
    freeTree(root);
    return 0;
}