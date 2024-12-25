#include "../lineUtils/lineUtils.h"
#include <stdio.h>

int main() {
  char *line;
  line = calloc(sizeof(*line), MAX_LINE_LEN); // выделяем место под строку
  if (line == NULL) {
    fprintf(stderr, "Память не выделилась\n");
    EXIT_FAILURE;
  }
  while (scanf("%1023[^\n]%*c", line) != EOF) {
    int c = getchar(); // используется только чтобы обработать краевой случай
    if (c != '\n') {   // проверка на пустую строку
      ungetc(c, stdin); // возвращаем символ обратно в буфер
    }
    printf("\"%s\"\n", line);
    if (myStrlen(line) > 0) {
      deleteSpaces(line);
      deleteDuplicates(line, true);
    }
    printf("\"%s\"\n", line);
    free(line);
    line = calloc(sizeof(*line), MAX_LINE_LEN);
    if (line == NULL) {
      fprintf(stderr, "Память не выделилась\n");
      EXIT_FAILURE;
    }
  }
  free(line);
  return 0;
}