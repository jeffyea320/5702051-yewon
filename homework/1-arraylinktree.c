#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

void GenerateArrayTree(int *tree)
{
    int List[] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};

    for (int i = 0; i < 15; i++)
    {
        tree[i] = List[i];
    }

    for (int i = 0; i < 15; i++)
    {
        printf("%d", tree[i]);
    }

    printf("\n");
}

void ArrayPreOrder(int *tree, int index, int size)
{

    if (index < size && tree[index] != -1)
    {
        printf("[%2d]", tree[index]);
        ArrayPreOrder(tree, 2 * index + 1, size);
        ArrayPreOrder(tree, 2 * index + 2, size);
    }
}

void ArrayInOrder(int *tree, int index, int size)
{
    if (index < size && tree[index] != -1)
    {
        ArrayInOrder(tree, 2 * index + 1, size);
        printf("[%2d]", tree[index]);
        ArrayInOrder(tree, 2 * index + 2, size);
    }
}

void ArrayPostOrder(int *tree, int index, int size)
{
    if (index < size && tree[index] != -1)
    {
        ArrayPostOrder(tree, 2 * index + 1, size);
        ArrayPostOrder(tree, 2 * index + 2, size);
        printf("[%2d]", tree[index]);
    }
}

void ArrayOrders(int *tree)
{
    ArrayPreOrder(tree, 0, 15);
    printf("\n");
    ArrayInOrder(tree, 0, 15);
    printf("\n");
    ArrayPostOrder(tree, 0, 15);
    printf("\n");
}

// void PlaceNode(TreeNode *node, int direction, int data)
// {
//     // 먼저 노드 만들어 두기
//     TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
//     newNode->data = data;
//     newNode->left = NULL;
//     newNode->right = NULL;
//     // 왼쪽일 경우
//     if (direction == 0)
//     {
//         if (node->left == NULL)
//         {
//             node->left = newNode; // 노드 왼쪽이 비었으면 왼쪽에 새 노드 연결
//         }
//         else
//         {
//             if (node->left->left == NULL)
//             {
//                 PlaceNode(node->left, direction, data); // 노드 왼쪽이 있고 왼쪽왼쪾이 비었으면 노드의 왼쪽 노드로 다시 함수 호출
//             }
//             else if(node->right->left == NULL)
//             { // 노드 왼쪽이 있고 왼쪽왼쪽도 있으면 노드 오른쪽으로 가서 왼쪽 검사
//                 PlaceNode(node->right, direction, data);
//             }
//         }
//     }
//     // 오른쪽일 경우
//     if (direction == 1)
//     {
//         if (node->right == NULL)
//         {
//             node->right = newNode; // 노드 오른쪽이 비었으면 오른쪽에 새 노드 연결
//         }
//         else
//         {
//             if (node->left->right == NULL)
//             {
//                 PlaceNode(node->left, direction, data);
//             }
//             else
//             {
//                 PlaceNode(node->right, direction, data);
//             }
//         }
//     }
// }

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

    // for (int j = 0; j < 14; j++)
    // {
    //     PlaceNode(root, direction, List[j]);
    //     if (direction == 0)
    //     {
    //         direction = direction + 1;
    //     }
    //     else if (direction == 1)
    //     {
    //         direction = direction - 1;
    //     }
    // }

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

void LinkPreOrder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("[%2d]", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

void LinkInOrder(TreeNode *root)
{
    if (root != NULL)
    {
        LinkInOrder(root->left);
        printf("[%2d]", root->data);
        LinkInOrder(root->right);
    }
}

void LinkPostOrder(TreeNode *root)
{
    if (root != NULL)
    {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("[%2d]", root->data);
    }
}

void LinkOrders(TreeNode *root)
{
    LinkPreOrder(root);
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
}

int main()
{
    int arr[15];

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateArrayTree(arr);
    GenerateLinkTree(root);

    printf("배열 트리 출력 결과\n");
    ArrayOrders(arr);
    printf("링크 트리 출력 결과\n");
    LinkOrders(root);

    return 0;
}

//           1
//        /     \
//      2          9
//     /  \        / \
//    3     5    10   13
//   / \   / \   / \  / \
//  4   6 7  8 11  12 14 15
