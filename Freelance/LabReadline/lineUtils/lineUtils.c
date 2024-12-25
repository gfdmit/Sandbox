#include "lineUtils.h"
#include <stdio.h>

// Удаляет пробелы в начале и в конце, а так же заменяет
// несколько подряд идущих пробелов на один пробел
void deleteSpaces(char *line) {
  char *pointerLine = line;
  bool isSpace = false;

  while (*line == ' ') {
    line++;
  }

  while (*line != '\0') {
    if (*line == ' ') {
      if (!isSpace) {
        *pointerLine++ = ' ';
      }
      isSpace = true;
    } else {
      *pointerLine++ = *line;
      isSpace = false;
    }
    line++;
  }

  if (pointerLine > line && *(pointerLine - 1) == ' ') {
    pointerLine--;
  }

  *pointerLine = '\0';
}

// Удаляет из каждого слова строки все повторяющиеся символы
// (кроме первого вхождения)
// mode - выбор лабораторной (а или b)
// mode false - lab4a, mode true - lab4b
void deleteDuplicates(char *line, bool mode) {
  char *token = NULL;
  char *pointer = line;
  char *tempLine = NULL;
  if (mode) {
    tempLine = malloc(myStrlen(line) + 1);
  } else {
    tempLine = malloc(strlen(line) + 1);
  }
  if (tempLine == NULL) {
    fprintf(stderr, "Память не выделилась\n");
    return;
  }
  if (mode) {
    myStrcpy(tempLine, line);
  } else {
    strcpy(tempLine, line);
  }

  if (mode) {
    token = myStrtok(tempLine, " ");
  } else {
    token = strtok(tempLine, " ");
  }

  while (token != NULL) {
    deleteDuplicateSymbols(token, mode);
    while (*token != '\0') {
      *line++ = *token++;
    }
    *line++ = ' ';
    if (mode) {
      token = myStrtok(NULL, " ");
    } else {
      token = strtok(NULL, " ");
    }
  }

  if (line > pointer && *(line - 1) == ' ') {
    line--;
  }

  *line = '\0';

  free(tempLine);
}

// Удаляет из слова повторяющиеся символы (кроме первого вхождения)
// mode - выбор лабораторной (а или b)
// mode false - lab4a, mode true - lab4b
void deleteDuplicateSymbols(char *word, bool mode) {
  size_t wordLen = 0;
  int pos = 0;

  if (mode) {
    wordLen = myStrlen(word);
  } else {
    wordLen = strlen(word);
  }

  for (int i = 0; i < wordLen; i++) {
    int j = 0;
    for (j = 0; j < pos; j++) {
      if (word[i] == word[j]) {
        break;
      }
    }
    if (j == pos) {
      word[pos++] = word[i];
    }
  }

  word[pos] = '\0';
}