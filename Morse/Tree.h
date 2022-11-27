#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct sBinTreeNode BinTreeNode;
typedef struct sBinTree BinTree;
struct sBinTreeNode {
	int data;
	struct sBinTreeNode* left;
	struct sBinTreeNode* right;
};
struct sBinTree {
	int size; // On peut également ajouter la hauteur si besoin
	struct sBinTreeNode* root;
};

BinTree* Tree_New(void);
BinTreeNode* TreeNode_New(int value);
void breadthFirstPrint(BinTree* tree);
void depthFirstPrint(BinTree* tree);
void Tree_Print(BinTree* tree);

void preOrderPrintRec(BinTreeNode* node);
void preOrderPrint(BinTree* tree);

void inOrderPrintRec(BinTreeNode* node);
void inOrderPrint(BinTree* tree);

void postOrderPrintRec(BinTreeNode* node);
void postOrderPrint(BinTree* tree);

void Tree_DeleteRec(BinTreeNode* node);
void Tree_Delete(BinTree* tree);

int Tree_HeightRec(BinTreeNode* node);
int Tree_Height(BinTree* tree);

int Tree_LeafCountRec(BinTreeNode* node);
int Tree_LeafCount(BinTree* tree);

int Tree_SizeRec(BinTreeNode* node);
int Tree_Size(BinTree* tree);

int Tree_IsPerfect(BinTree* tree);
int Tree_IsComplete(BinTree* tree);