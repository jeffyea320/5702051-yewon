#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

TreeNode *new_node(int key)
{
    TreeNode *temp;

    temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;

    return temp;
}

TreeNode *insert_node(TreeNode *root, int key)
{
    if (root == NULL)
        new_node(key);

    if (root->data == key)
        return root;
    else if (root->data > key)
        root->left = insert_node(root->left, key);
    else
        root->right = insert_node(root->right, key);

    return root;
}

void inorder_traversal(TreeNode *root)
{
    if (root != NULL)
    {
        inorder_traversal(root->left);
        printf("[%2d]", root->data);
        inorder_traversal(root->right);
    }
}

TreeNode *search_bst(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    else
    {
        if (root->data == key)
            return root;
        else if (root->data > key)
            return search_bst(root->left, key);
        else
            return search_bst(root->right, key);
    }
}

TreeNode *min_value_node(TreeNode *root)
{
    TreeNode *current = root;

    while (current->left != NULL)
        current = current->left;
    return current;
}

TreeNode *delete_node(TreeNode *root, int key)
{
    TreeNode *temp = NULL;

    if (root == NULL)
        return root;

    else if (root->data > key)
        root->left = delete_node(root->left, key);
    else if (root->data < key)
        root->right = delete_node(root->right, key);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL && root->right != NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            temp = min_value_node(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
            return root;
        }
    }

    return root;
}