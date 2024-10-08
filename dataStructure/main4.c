#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main()
{
    TreeNode *bst = NULL, *temp = NULL;

    bst = insert_node(bst, 14);
    bst = insert_node(bst, 5);
    bst = insert_node(bst, 3);
    bst = insert_node(bst, 2);
    bst = insert_node(bst, 9);
    bst = insert_node(bst, 8);
    bst = insert_node(bst, 18);
    bst = insert_node(bst, 15);
    bst = insert_node(bst, 19);
    bst = insert_node(bst, 16);
    bst = insert_node(bst, 20);

    printf("inorder \n");
    inorder_traversal(bst);
    printf("\n");

    temp = search_bst(bst, 9);
    if (temp != NULL)
        printf("Search Success: %d\n", temp->data);
    else
        printf("Search Fail: 9");
}