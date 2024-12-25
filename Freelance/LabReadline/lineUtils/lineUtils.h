#ifndef LINEUTILS_H
#define LINEUTILS_H

#include <readline/readline.h>
#include "../mystring/mystring.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

void deleteSpaces(char *);

void deleteDuplicates(char *, bool);

void deleteDuplicateSymbols(char *, bool);

#endif
