#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    int data;
    struct tree_node *right, *left;
} TreeNode;

typedef struct thread_node
{
    int data;
    struct thread_node *left, *right;
    int ltag, rtag;
} ThreadTree;

TreeNode *new_node(int key)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = key;
    node->left = node->right = NULL;
    return node;
}

TreeNode *insert_node(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return new_node(key);
    }

    if (key < root->data)
    {
        root->left = insert_node(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = insert_node(root->right, key);
    }

    return root;
}

TreeNode *GenerateBinaryTree(int inputData[])
{
    TreeNode *root = NULL;

    for (int i = 0; i < 15; i++)
    {
        root = insert_node(root, inputData[i]);
    }

    return root;
}

void BinaryTreeInOrder(TreeNode *root)
{
    if (root != NULL)
    {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadTree *CreateNode(int data)
{
    ThreadTree *node = (ThreadTree *)malloc(sizeof(ThreadTree));
    node->data = data;
    node->left = node->right = NULL;
    node->ltag = 0;
    node->rtag = 0;
    return node;
}

ThreadTree *insert_thread_node(ThreadTree *root, int key)
{
    if (root == NULL)
    {
        return CreateNode(key);
    }
    if (key < root->data)
    {
        root->left = insert_thread_node(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = insert_thread_node(root->right, key);
    }
    return root;
}

void CreateThreads(ThreadTree *root, ThreadTree **prev)
{
    if (root == NULL)
        return;

    CreateThreads(root->left, prev);

    if (root->left == NULL)
    {
        root->ltag = 1;
        root->left = *prev;
    }
    if (*prev != NULL && (*prev)->right == NULL)
    {
        (*prev)->rtag = 1;
        (*prev)->right = root;
    }

    *prev = root;

    CreateThreads(root->right, prev);
}

ThreadTree *GenerateThreadTree(int inputData[])
{
    ThreadTree *root = NULL;
    for (int i = 0; i < 15; i++)
    {
        root = insert_thread_node(root, inputData[i]);
    }

    ThreadTree *prev = NULL;
    CreateThreads(root, &prev);

    return root;
}

void ThreadTreeInOrder(ThreadTree *root)
{
    if (root == NULL)
        return;

    ThreadTree *temp = root;
    while (temp->ltag == 0 && temp->left != NULL)
    {
        temp = temp->left;
    }

    while (temp != NULL)
    {
        printf("%d ", temp->data);

        if (temp->rtag == 1)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->right;
            while (temp != NULL && temp->ltag == 0 && temp->left != NULL)
            {
                temp = temp->left;
            }
        }
    }
}

int main()
{
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};

    TreeNode *root = GenerateBinaryTree(inputData);
    printf("Binary tree inrder: ");
    BinaryTreeInOrder(root);

    printf("\n");

    ThreadTree *troot = GenerateThreadTree(inputData);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);

    free(root);
    free(troot);

    return 0;
}