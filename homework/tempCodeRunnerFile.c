// void PlaceNode(TreeNode *node, int direction, int data)
//  {
//      if (node == NULL)
//          return;

//     // 방향에 따라 왼쪽 또는 오른쪽 자식 노드를 설정합니다.
//     if (direction == 0)
//     {
//         // 현재 노드의 데이터 설정
//         node->data = data;

//         // 왼쪽 자식 노드 생성
//         node->left = (TreeNode *)malloc(sizeof(TreeNode));
//         node->left->left = node->left->right = NULL;

//         // 오른쪽 자식 노드 생성
//         node->right = (TreeNode *)malloc(sizeof(TreeNode));
//         node->right->left = node->right->right = NULL;
//     }
//     else if (direction == 1)
//     {
//         // 왼쪽 자식 노드에 데이터 추가
//         PlaceNode(node->left, direction, data);
//     }
//     else if (direction == 2)
//     {
//         // 오른쪽 자식 노드에 데이터 추가
//         PlaceNode(node->right, direction, data);
//     }
// }

// void GenerateLinkTree(TreeNode *root)
// {
//     // 트리의 루트 노드를 생성합니다.
//     root = (TreeNode *)malloc(sizeof(TreeNode));
//     root->data = 1;
//     root->left = NULL;
//     root->right = NULL;

//     // 트리의 노드를 배치합니다.
//     PlaceNode(root, 0, 2); // 이 호출은 현재 노드에 데이터를 추가하는 예시입니다.
// }

// void LinkPreOrder(TreeNode *root)
// {
//     if (root != NULL)
//     {
//         printf("[%2d]", root->data);
//         LinkPreOrder(root->left);
//         LinkPreOrder(root->right);
//     }
// }

// void LinkInOrder(TreeNode *root)
// {
//     if (root != NULL)
//     {
//         LinkInOrder(root->left);
//         printf("[%2d]", root->data);
//         LinkInOrder(root->right);
//     }
// }

// void LinkPostOrder(TreeNode *root)
// {
//     if (root != NULL)
//     {
//         LinkPostOrder(root->left);
//         LinkPostOrder(root->right);
//         printf("[%2d]", root->data);
//     }
// }

// void LinkOrders(TreeNode *root)
// {
//     LinkPreOrder(root);
//     LinkInOrder(root);
//     LinkPostOrder(root);
// }