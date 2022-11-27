#pragma once

#include <stdio.h>
#include <stdlib.h>

//Liste doublement chainées
typedef struct sDListNode
{
	void* value;
	struct sDListNode* previous;
	struct sDListNode* next;
}DListNode;

typedef struct sDList
{
	DListNode* sentinel;
	int	size;
}DList;

//Déclaration de fonctions

DList* createList();
void insertFirst(DList* list, DListNode* node);
void insertLast(DList* list, DListNode* node);
void* pop(DList* list);
DListNode* pop2(DList* list);
DListNode* firstOf(DList* list, void* value, int (*compareData)(void*, void*));
DListNode* lastOf(DList* list, void* value, int (*compareData)(void*, void*));
void insertSorted(DList* list, DListNode* node, int reverse, int (*compareData)(void*, void*));
DListNode* get(DList* list, int index);
void insertBefore(DList* list, DListNode* node, int index);
void insertAfter(DList* list, DListNode* node, int index);
void* removeAt(DList* list, int index);
DList* slice(DList* list, int i, int j);
DList* fusion(DList* list1, DList* list2, int (*compareData)(void*, void*));
DListNode* createNode(void* value);