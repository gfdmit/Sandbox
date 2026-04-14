#ifndef UTILS_H
#define UTILS_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 512
#define MAX_NAME_SIZE 256
#define ID_LENGTH 8

typedef struct {
  char id[ID_LENGTH + 1];
  char name[MAX_NAME_SIZE + 1];
  int count;
} Detail;

typedef struct {
  char *inputFile;
  char *outputFile;
  char *inputType;
  char *outputFormat;
} Flags;

void printUsage();

Flags parseFlags(int argc, char *argv[]);

Detail parseString(char *string);

#endif