#pragma once

typedef int value;

struct tree_node
{
    value data;
    struct tree_node *left, *right;
};

typedef struct tree_node TreeNode;

extern int level_order(TreeNode *root);
extern int sum_of_tree_nodes(TreeNode *root);
extern int get_node_count(TreeNode *root);
extern int get_height(TreeNode *root);