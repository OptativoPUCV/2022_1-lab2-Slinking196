#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *newList = (List *) malloc (sizeof(List));
    newList->current = NULL;
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node *newNode = createNode(data);
    
    if (list == NULL) {
        list->head = newNode;
        list->current = list->head;
        list->tail = list->head;
    }
    else {
        newNode->next = list->head;
        list->head = newNode;
        list->current = list->head;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *newNode = createNode(data);

    if (list->current == list->tail) {
        newNode->prev = list->current;
        list->current->next = newNode;
        list->tail = newNode;
    }
    else {
        newNode->prev = list->current;
        newNode->next = list->current->next;
        list->current->next = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node *eliminateNode = list->current;

    if (list->current == list->head) {
        list->current->next->prev = NULL;
        list->head = list->current->next;
    }
    else {
        if (list->current == list->tail) {
            list->current->prev->next = NULL;
            list->tail = list->current ->prev;
        }
        else {
            list->current->prev->next = list->current->next;
            list->current->next->prev = list->current->prev;
        }
    }
    return eliminateNode->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}