#include "Tree.h"
#include "list.h"
#include <math.h>

BinTree* Tree_New(void)
{
	//Retourne un pointeur sur la variable allouée
	return calloc(1, sizeof(BinTree));
}

BinTreeNode* TreeNode_New(int value)
{
	//Déclaration d'un nouveau noeud
	BinTreeNode* node = calloc(1, sizeof(BinTreeNode));
	//La valeur de node est value en parametre
	if (node) node->data = value;
	return node;
}

int isEmpty(DList* file)
{
	return(file->sentinel->next == NULL) ? 1 : 0;
}

void breadthFirstPrint(BinTree* tree)
{
	//Enfilé insertLast
	//Défilé pop
	DList* list = createList();
	insertLast(list, createNode(tree->root));
	while (list->size > 0)
	{
		BinTreeNode* node = (BinTreeNode*)pop(list);
		printf("%d ", (node)->data);
		if ((node)->left != NULL)
			insertLast(list, createNode((node)->left));
		if ((node)->right != NULL)
			insertLast(list, createNode((node)->right));
	}
}

void depthFirstPrint(BinTree* tree)
{
	DList* pile = createList();
	insertFirst(pile, createNode(tree->root));
	while (pile->size > 0)
	{
		BinTreeNode* node = (BinTreeNode*)pop(pile);
		printf("%d ", (node)->data);
		if ((node)->right != NULL)
			insertFirst(pile, createNode((node)->right));
		if ((node)->left != NULL)
			insertFirst(pile, createNode((node)->left));
	}
}

void Tree_Print(BinTree* tree)
{

}

void preOrderPrintRec(BinTreeNode* node)
{
	if (node)
	{
		printf("%d ", node->data);
		preOrderPrintRec(node->left);
		preOrderPrintRec(node->right);
	}
}

void preOrderPrint(BinTree* tree)
{
	if (tree)
	{
		BinTreeNode* node = tree->root;
		preOrderPrintRec(node);
	}
}

void inOrderPrintRec(BinTreeNode* node)
{
	if (node)
	{
		inOrderPrintRec(node->left);
		printf("%d ", node->data);
		inOrderPrintRec(node->right);
	}
}

void inOrderPrint(BinTree* tree)
{
	if (tree)
	{
		BinTreeNode* node = tree->root;
		inOrderPrintRec(node);
	}
}

void postOrderPrintRec(BinTreeNode* node)
{
	if (node)
	{
		postOrderPrintRec(node->left);
		postOrderPrintRec(node->right);
		printf("%d ", node->data);
	}
}

void postOrderPrint(BinTree* tree)
{
	if (tree)
	{
		BinTreeNode* node = tree->root;
		postOrderPrintRec(node);
	}
}

void Tree_DeleteRec(BinTreeNode* node)
{
	if (node)
	{
		Tree_DeleteRec(node->left);
		Tree_DeleteRec(node->right);
		printf("%d ", node->data);
	}
}

void Tree_Delete(BinTree* tree)
{
	if (tree)
	{
		BinTreeNode* node = tree->root;
		postOrderPrintRec(node);
	}
}

int Tree_HeightRec(BinTreeNode* node)
{
	if (!node) return 0;
	if (!(node->left) && !(node->right)) return 0;
	int leftHeight = Tree_HeightRec(node->left);
	int rightHeight = Tree_HeightRec(node->right);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int Tree_Height(BinTree* tree)
{
	if (!tree)
		return -1;
	return Tree_HeightRec(tree->root);
}

int Tree_LeafCountRec(BinTreeNode* node)
{
	if (!node)
		return 0;
	if (!node->left && !node->right)
		return 1;
	return Tree_LeafCountRec(node->left) + Tree_LeafCountRec(node->right);
}

int Tree_LeafCount(BinTree* tree)
{
	if (!tree)
		return -1;
	return Tree_LeafCountRec(tree->root);
}

int Tree_SizeRec(BinTreeNode* node)
{
	if (!node)
		return 0;
	return Tree_SizeRec(node->left) + Tree_SizeRec(node->right) + 1;
}

int Tree_Size(BinTree* tree)
{
	if (!tree)
		return -1;
	return Tree_SizeRec(tree->root);
}

int Tree_IsPerfect(BinTree* tree)
{
	if (!tree)
		return -1;
	if (pow(2, Tree_Height(tree)) == Tree_LeafCount(tree))
		return 1;
	return 0;
}

int Tree_IsComplete(BinTree* tree)
{
	if (!tree)
		return -1;
	if (Tree_Size(tree) == pow(2, Tree_Height(tree)) - 1)
		return 1;
	return 0;
}