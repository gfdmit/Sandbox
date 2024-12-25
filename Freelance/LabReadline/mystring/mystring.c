#include "mystring.h"

size_t myStrlen(const char *str) {
  const char *s = "";
  for (s = str; *s; ++s) {
  }
  return (s - str);
}

char *myStrtok(char *str, const char *delim) {
  static char *token_next = NULL;
  char *token_start;

  if (str == NULL) {
    str = token_next;
    if (str == NULL) {
      return NULL;
    }
  }

  while (*str != '\0') {
    const char *d = delim;
    while (*d != '\0') {
      if (*str == *d) {
        break;
      }
      d++;
    }
    if (*d == '\0') {
      break;
    }
    str++;
  }

  if (*str == '\0') {
    token_next = NULL;
    return NULL;
  }

  token_start = str;

  while (*str != '\0') {
    const char *d = delim;
    while (*d != '\0') {
      if (*str == *d) {
        *str = '\0';
        token_next = str + 1;
        return token_start;
      }
      d++;
    }
    str++;
  }

  token_next = NULL;
  return token_start;
}

char *myStrcpy(char *dest, const char *src) {
  char *original_dest = dest;

  while ((*dest++ = *src++))
    ;

  return original_dest;
}