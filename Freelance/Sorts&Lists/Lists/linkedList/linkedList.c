#include "linkedList.h"
#include <stdbool.h>
#include <stdio.h>

void listInit(list_t *list) { list->head = list->tail = NULL; }

void listClear(list_t *list) {
  if (list->head == NULL || list->tail == NULL) {
    list->head = NULL;
    list->tail = NULL;
    return;
  }
  node_t *iterator = list->head;
  node_t *next;
  while (iterator) {
    next = iterator->next;
    free(iterator);
    iterator = next;
  }
  list->head = NULL;
  list->tail = NULL;
}

node_t *listBegin(list_t *list) { return list->head; }

node_t *listEnd(list_t *list) { return list->tail->next; }

void listPushFront(list_t *list, char item) {
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation error: node\n");
  }
  newNode->data = item;
  newNode->next = list->head;

  list->head = newNode;
  if (list->tail == NULL) {
    list->tail = newNode;
  }
}

void listPushBack(list_t *list, char item) {
  if (list->tail == NULL) {
    return listPushFront(list, item);
  }
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation error: node\n");
  }
  newNode->data = item;
  newNode->next = NULL;

  list->tail->next = newNode;
  list->tail = newNode;
}

void listPopFront(list_t *list) {
  if (listIsEmpty(*list)) {
    fprintf(stderr, "Pop empty list\n");
    return;
  }
  node_t *newHead = list->head->next;
  free(list->head);
  list->head = newHead;
}

void listPopBack(list_t *list) {
  if (listIsEmpty(*list)) {
    fprintf(stderr, "Pop empty list\n");
    return;
  }
  if (list->head == list->tail) {
    return listPopFront(list);
  }
  node_t *iterator = list->head;
  while (iterator->next != list->tail) {
    iterator = iterator->next;
  }
  iterator->next = NULL;
  free(list->tail);
  list->tail = iterator;
}

void listPopNextNode(list_t *list, node_t *node) {
  if (listIsEmpty(*list)) {
    fprintf(stderr, "Pop empty list\n");
    return;
  }
  if (node == NULL) {
    return listPopFront(list);
  }
  if (node->next == NULL) {
    fprintf(stderr, "Pop empty node\n");
  }
  node_t *nodeToDelete = node->next;
  node->next = node->next->next;
  free(nodeToDelete);
}

void listPrint(list_t list) {
  node_t *iterator = list.head;
  printf("\"");
  while (iterator != NULL) {
    printf("%c", iterator->data);
    iterator = iterator->next;
  }
  printf("\"\n");
  fflush(stdout);
}

bool listIsEmpty(list_t list) {
  return (list.head == NULL || list.tail == NULL) ? true : false;
}

char listFront(list_t list) { return list.head->data; }

char listBack(list_t list) { return list.tail->data; }

void listTransform(list_t *list) {
  while (!listIsEmpty(*list) && list->head->data != '.') {
    listPopFront(list);
  }
  while (!listIsEmpty(*list) && list->tail->data != ';') {
    listPopBack(list);
  }
}