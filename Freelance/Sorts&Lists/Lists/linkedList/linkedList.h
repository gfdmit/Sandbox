#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  char data;
  struct node_t *next;
} node_t;

typedef struct list_t {
  node_t *head;
  node_t *tail;
} list_t;

void listInit(list_t *list);
void listClear(list_t *list);
node_t *listBegin(list_t *list);
node_t *listEnd(list_t *list);
void listPushFront(list_t *list, char item);
void listPushBack(list_t *list, char item);
void listPopFront(list_t *list);
void listPopBack(list_t *list);
void listPopNextNode(list_t *list, node_t *node);
void listPrint(list_t list);
bool listIsEmpty(list_t list);
char listFront(list_t list);
char listBack(list_t list);
void listTransform(list_t *list);

#endif /* LINKEDLIST_H */