#include "list.h"


DList* createList()
{
    DList* list = (DList*)calloc(1, sizeof(DList));
    if (!list) return NULL;
    list->sentinel = (DListNode*)calloc(1, sizeof(DListNode));
    if (list->sentinel)
    {
        list->sentinel->next = list->sentinel;
        list->sentinel->previous = list->sentinel;
    }

    return list;
}

DListNode* createNode(void* value)
{
    DListNode* node = (DListNode*)calloc(1, sizeof(DListNode));

    if (!node) return NULL;
    node->value = value;
    return node;
}

void insertFirst(DList* list, DListNode* node) {
    node->previous = list->sentinel;
    node->next = list->sentinel->next;
    node->previous->next = node;
    node->next->previous = node;
    list->size++;
}

void insertLast(DList* list, DListNode* node)
{
    node->next = list->sentinel;
    node->previous = list->sentinel->previous;
    node->previous->next = node;
    node->next->previous = node;
    list->size++;
}

void* pop(DList* list) {
    if (list->size == 0) return NULL;

    DListNode* node = list->sentinel->next;
    node->next->previous = node->previous;
    node->previous->next = node->next;
    void* value = node->value;
    free(node);
    list->size--;
    return value;
}

DListNode* pop2(DList* list)
{
    if (list->size == 0) return NULL;

    DListNode* node = list->sentinel->next;
    node->next->previous = node->previous;
    node->previous->next = node->next;
    node->previous = NULL;
    node->next = NULL;
    list->size--;
    return node;
}

DListNode* firstOf(DList* list, void* value, int (*compareData)(void*, void*))
{
    DListNode* current = list->sentinel->next;
    for (int i = 0; i < list->size; i++)
    {
        if (!compareData(value, current->value))
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

DListNode* lastOf(DList* list, void* value, int (*compareData)(void*, void*))
{
    DListNode* current = list->sentinel->previous;
    for (int i = list->size; i > 0; i--)
    {
        if (!compareData(value, current->value))
        {
            return current;
        }
        current = current->previous;
    }
    return NULL;
}

void insertSorted(DList* list, DListNode* node, int reverse, int (*compareData)(void*, void*))
{
    DListNode* current = list->sentinel->next;
    while ((current != list->sentinel) &&
        ((compareData(node->value, current->value) > 0) || (reverse)) &&
        ((compareData(node->value, current->value) < 0) || (!reverse))) {
        current = current->next;
    }
    node->next = current;
    node->previous = current->previous;
    node->previous->next = node;
    node->next->previous = node;
    list->size++;
}

DListNode* get(DList* list, int index) {
    DListNode* current = NULL;

    if (0 <= index && index < list->size) {
        current = list->sentinel->next;
        while ((current != list->sentinel) && (index > 0)) {
            current = current->next;
            index--;
        }
        return current;
    }
    if ((index < 0) && (-index <= list->size)) { // index négatif, optimise le temps de recherche
        current = list->sentinel->previous;
        while ((current != list->sentinel) && (index < -1)) {
            current = current->previous;
            index++;
        }
    }
    return current;
}

void insertBefore(DList* list, DListNode* node, int index)
{
    DListNode* current = get(list, index);
    node->next = current;
    node->previous = current->previous;
    node->previous->next = node;
    node->next->previous = node;
    list->size++;
}

void insertAfter(DList* list, DListNode* node, int index) {
    DListNode* current = get(list, index);
    DListNode* next = current->next;
    node->next = next;
    node->previous = current;
    current->next = node;
    next->previous = node;
    list->size++;
}

void* removeAt(DList* list, int index) {
    if (list->size == 0) return NULL;
    DListNode* node = get(list, index);
    if (node == list->sentinel) return NULL;

    node->next->previous = node->previous;
    node->previous->next = node->next;
    void* value = node->value;
    free(node);
    list->size--;
    return value;
}

DList* slice(DList* list, int i, int j) {
    if (i < 0) i = list->size + i;
    if (j < 0) j = list->size + j;
    if ((i < 0) || (i >= list->size) || (j < 0) || (j >= list->size) || (i > j)) return NULL;

    DListNode* node1 = get(list, i);
    DListNode* node2 = get(list, j);
    DList* list2 = createList();

    node1->previous->next = node2->next;
    node2->next->previous = node1->previous;
    node1->previous = list2->sentinel;
    node2->next = list2->sentinel;
    list2->sentinel->next = node1;
    list2->sentinel->previous = node2;

    list2->size = j - i + 1;
    list->size -= list2->size;

    return list2;
}

DList* fusion(DList* list1, DList* list2, int (*compareData)(void*, void*)) {
    DList* list3 = createList();

    while ((list1->size > 0) || (list2->size > 0)) {
        if ((list2->size == 0) || ((list1->size > 0) && (compareData(list1->sentinel->next->value, list2->sentinel->next->value) <= 0))) {
            insertLast(list3, pop2(list1));
        }
        else {
            insertLast(list3, pop2(list2));
        }
    }
    //destroy(list1);
    //destroy(list2);
    return list3;
}