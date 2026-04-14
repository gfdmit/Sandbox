#include "utils.h"

void printUsage() {
  printf("Usage: program -i <inputFile> -o <outputFile> -t <inputType> -f "
         "<outputFormat>\n");
  printf("  -i <inputFile>    : Input file (optional, default is stdin)\n");
  printf("  -o <outputFile>   : Output file (optional, default is stdout)\n");
  printf("  -t <inputType> : Input type (text, binary, stdin)\n");
  printf("  -f <outputFormat> : Output format (text, binary, stdout)\n");
}

Flags parseFlags(int argc, char *argv[]) {
  Flags flags = {};
  int opt;
  while ((opt = getopt(argc, argv, "i:o:t:f:")) != -1) {
    switch (opt) {
    case 'i':
      flags.inputFile = optarg;
      break;
    case 'o':
      flags.outputFile = optarg;
      break;
    case 't':
      flags.inputType = optarg;
      break;
    case 'f':
      flags.outputFormat = optarg;
      break;
    default:
      printUsage();
      exit(EXIT_FAILURE);
    }
  }
  return flags;
}

Detail parseString(char *str) {
  char *strCopy = strdup(str);
  Detail retVal = {"", "", 0};
  Detail detail = {"", "", 0};

  char *id = strtok(strCopy, ";");
  if (id) {
    if (strlen(id) != 8) {
      fprintf(stderr, "Id length is not 8: %s\n", id);
      free(strCopy);
      return retVal;
    }
    strncpy(detail.id, id, sizeof(detail.id));
    detail.id[sizeof(detail.id) - 1] = '\0';
  } else {
    fprintf(stderr, "Id is empty\n");
    free(strCopy);
    return retVal;
  }

  char *name = strtok(NULL, ";");
  if (name) {
    strncpy(detail.name, name, MAX_NAME_SIZE);
    detail.name[sizeof(detail.name) - 1] = '\0';
  } else {
    fprintf(stderr, "Name is empty\n");
    free(strCopy);
    return retVal;
  }

  char *count = strtok(NULL, ";");
  if (count) {
    int number = atoi(count);
    if (number == 0 && (strlen(count) != 1 || *count != '0')) {
      fprintf(stderr, "Count must be number\n");
      free(strCopy);
      return retVal;
    }
    detail.count = number;
  } else {
    fprintf(stderr, "Count is empty\n");
    free(strCopy);
    return retVal;
  }

  free(strCopy);
  retVal = detail;
  return retVal;
}