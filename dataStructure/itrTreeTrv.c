#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "itrTreeTrv.h"

TreeNode *new_node(int value)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp = value;
	temp->left = temp->right = NULL;
	return temp;
}

void insert_node(TreeNode *root, int value)
{
	TreeNode *temp;
	TreeNode *prev;
	if (root == NULL)
		return new_node(value);

	temp = root;
	while (temp != NULL)
	{
		if (temp->data == value)
			return temp;
		else if (temp->data > value)
		{
			prev = temp;
			temp = temp->left;
		}
		else
		{
			prev = temp;
			temp = temp->right;
		}
	}
	temp = new_node(value);
	if (prev->data > value)
		prev->left = temp;
	else
		prev->right = temp;

	return root;
}

void itr_inorder_traversal(TreeNode *root)
{
	LinkedStackType s;
	TreeNode *nptr = root;

	init(&s);

	while (nptr != NULL || !is_empty(&s))
	{
		while (nptr != NULL)
		{
			push(&s, nptr);
			nptr = nptr->left;
		}

		nptr = pop(&s);
		printf("[%2d]", nptr->data);

		nptr = nptr->right;
	}
}
