#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "levelTraversal.h"

int node_sum;

int get_height(TreeNode *root)
{
    int height;

    // height = 1+ max(get_height(root->left), get_height(root->right));
    height = 1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));

    return height;
}

int get_node_count(TreeNode *root)
{
    int count;

    count = 1 + get_node_count(root->left) + get_node_count(root->right);

    return count;
}

int sum_of_tree_nodes(TreeNode *root)
{
    int sum;

    if (root == NULL)
        return 0;
    sum = root->data + sum_of_tree_nodes(root->left) + sum_of_tree_nodes(root->right);

    return sum;
}

int level_order(TreeNode *ptr)
{
    QueueType q;

    init_queue(&q); // 큐 초기화

    if (ptr == NULL)
        return 0;
    enqueue(&q, ptr);
    while (!is_empty(&q))
    {
        ptr = dequeue(&q);
        printf(" [%d] ", ptr->data);
        node_sum += ptr->data;
        if (ptr->left)
            enqueue(&q, ptr->left);
        if (ptr->right)
            enqueue(&q, ptr->right);
    }
    return node_sum;
}
