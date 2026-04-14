#include "linkedList.h"
#include <stdbool.h>
#include <stdio.h>

void listInit(list_t *list) { list->head = list->tail = NULL; }

void listClear(list_t *list) {
  if (list->head == NULL || list->tail == NULL) {
    free(list->head);
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
    return;
  }
  node_t *iterator = listBegin(list);
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
  if (list->head == list->tail) {
    list->tail = NULL;
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
    return;
  }
  if (node->next->next == NULL) {
    return listPopBack(list);
  }
  node_t *nodeToDelete = node->next;
  node->next = node->next->next;
  free(nodeToDelete);
}

void listPrint(list_t list) {
  node_t *iterator = list.head;
  printf("\"");
  while (iterator) {
    printf("%c", iterator->data);
    iterator = iterator->next;
  }
  printf("\"\n");
}

bool listIsEmpty(list_t list) {
  if (list.head == NULL || list.tail == NULL) {
    return true;
  } else {
    return false;
  }
}

char listFront(list_t list) { return list.head->data; }

char listBack(list_t list) { return list.tail->data; }

void listTransform(list_t *list) {
  while (!listIsEmpty(*list) && listFront(*list) != '.') {
    listPopFront(list);
  }
  while (!listIsEmpty(*list) && listBack(*list) != ';') {
    listPopBack(list);
  }
  if (!listIsEmpty(*list)) {
    listDeleteSpaces(list);
  }
}

void listDeleteSpaces(list_t *list) {
  node_t *iterator = listBegin(list);
  node_t *prevIterator = listBegin(list);
  while (iterator->next->data == ' ') {
    listPopNextNode(list, iterator);
  }
  while (iterator->next->next != listEnd(list)) {
    if (iterator->data == ' ' && iterator->next->data == ' ') {
      listPopNextNode(list, iterator);
    } else {
      prevIterator = iterator;
      iterator = iterator->next;
    }
  }
  if (iterator->data == ' ') {
    listPopNextNode(list, prevIterator);
  }
}