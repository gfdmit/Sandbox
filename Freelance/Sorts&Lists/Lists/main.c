#include "linkedList/linkedList.h"
#include <stdio.h>

int main() {
  list_t list;
  listInit(&list);

  int ch;
  while ((ch = getchar()) != EOF) {
    if (ch == '\n') {
      listPrint(list);
      listTransform(&list);
      listPrint(list);
      listClear(&list);
    } else {
      listPushBack(&list, ch);
    }
  }
  if (!listIsEmpty(list)) {
    listPrint(list);
    listTransform(&list);
    listPrint(list);
    listClear(&list);
  }
}