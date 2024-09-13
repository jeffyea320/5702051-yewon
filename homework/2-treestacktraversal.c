#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef TreeNode *element;
typedef struct StackNode
{
    element data;
    struct StackNode *link;
} StackNode;

typedef struct
{
    StackNode *top;
} LinkedStackType;

// 초기화함수
void init(LinkedStackType *s)
{
    s->top = NULL;
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType *s)
{
    return (s->top == NULL);
}
// 포화상태 검출 함수
int is_full(LinkedStackType *s)
{
    return 0;
}
// 삽입 함수
void push(LinkedStackType *s, element item)
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

element pop(LinkedStackType *s)
{
    StackNode *temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    free(temp);

    return data;
}

void print_stack(LinkedStackType *s)
{
    for (StackNode *p = s->top; p != NULL; p = p->link)
        printf("%d->", p->data->data);
    printf("NULL \n");
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

void LinkPreOrder(TreeNode *root)
{
    LinkedStackType s;
    TreeNode *nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s))
    {

        while (nptr != NULL)
        {
            printf("push(%d) ", nptr->data);
            // printf("[%d]", nptr->data);
            push(&s, nptr);
            nptr = nptr->left;
        }

        // 왼쪽 자식이 없으면 스택에서 노드를 팝하고 오른쪽 자식으로 이동
        nptr = pop(&s);
        printf("pop(%d) ", nptr->data);
        printf("visit(%d)\n ", nptr->data);
        nptr = nptr->right;
    }
}

void LinkInOrder(TreeNode *root)
{
    LinkedStackType s;
    TreeNode *nptr = root;

    init(&s);

    while (nptr != NULL || !is_empty(&s))
    {
        while (nptr != NULL)
        {
            printf("push(%d) ", nptr->data);
            push(&s, nptr);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        // printf("[%2d]", nptr->data);
        printf("pop(%d) ", nptr->data);
        printf("visit(%d)\n ", nptr->data);

        nptr = nptr->right;
    }
}

void LinkPostOrder(TreeNode *root)
{
    LinkedStackType s;
    TreeNode *nptr = root;
    TreeNode *lastVisited = NULL;

    init(&s);

    while (nptr != NULL || !is_empty(&s))
    {
        while (nptr != NULL)
        {
            printf("push(%d) ", nptr->data);
            push(&s, nptr);
            nptr = nptr->left;
        }

        nptr = s.top->data;

        if (nptr->right == NULL || nptr->right == lastVisited)
        {
            nptr = pop(&s);
            printf("pop(%d) ", nptr->data);
            printf("visit(%d)\n", nptr->data);
            lastVisited = nptr;
            nptr = NULL;
        }
        else
        {
            nptr = nptr->right;
        }
    }
}

void LinkOrders(TreeNode *root)
{
    printf("LinkedPreOrder: \n");
    LinkPreOrder(root);
    printf("\nLinkedInOrder:\n");
    LinkInOrder(root);
    printf("\nLinkedPostOder:\n");
    LinkPostOrder(root);
}

int main()
{
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateLinkTree(root);

    LinkOrders(root);

    return 0;
}