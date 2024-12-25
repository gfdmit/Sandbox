#include "../lineUtils/lineUtils.h"

int main() {
  char *line = NULL;
  bool isEOF = false; // флаг, чтобы избежать while (true) и break, continue
  while (!isEOF) {
    line = readline(NULL);
    if (line == NULL) {
      isEOF = true;
    } else {
      printf("\"%s\"\n", line);
      deleteSpaces(line);
      deleteDuplicates(line, false);
      printf("\"%s\"\n", line);
    }
    free(line);
  }
  EXIT_SUCCESS;
}