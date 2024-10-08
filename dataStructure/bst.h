#pragma once

typedef struct tree_node
{
    int data;
    struct tree_node *right, *left;
} TreeNode;

extern TreeNode *insert_node(TreeNode *root, int key);
extern void inorder_traversal(TreeNode *root);
extern TreeNode *search_bst(TreeNode *root, int key);
extern TreeNode *delete_node(TreeNode *root, int key);