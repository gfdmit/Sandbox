#include "utils.h"

void printUsage() {
  printf("Usage: program -s <sorting> -l <field> -d <direction> -l <length> -c "
         "<count>\n");
  printf("  -s <sorting> : Sorting algorithm (gnome, heap, quick)\n");
  printf("  -f <field> : Structure field (id, name, count)\n");
  printf("  -d <direction> : Sort direction (desc, asc)\n");
  printf("  -l <length> : Array length (unsigned int > 0)\n");
  printf("  -c <count> : Array count (unsigned int > 0)\n");
}

Flags parseFlags(int argc, char *argv[]) {
  Flags flags = {};
  int opt;
  while ((opt = getopt(argc, argv, "s:f:d:l:c:")) != -1) {
    switch (opt) {
    case 's':
      flags.sorting = optarg;
      break;
    case 'f':
      flags.field = optarg;
      break;
    case 'd':
      flags.direction = optarg;
      break;
    case 'l':
      flags.arrLength = atoi(optarg);
      break;
    case 'c':
      flags.arrCount = atoi(optarg);
      break;
    default:
      printUsage();
      exit(EXIT_FAILURE);
    }
  }
  return flags;
}

Detail **generate(Flags flags) {
  Detail **arrDetails = (Detail **)malloc(flags.arrCount * sizeof(Detail *));
  if (arrDetails == NULL) {
    perror("Failed to allocate memory for arrays");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < flags.arrCount; i++) {
    arrDetails[i] = (Detail *)malloc(flags.arrLength * sizeof(Detail));
    if (arrDetails[i] == NULL) {
      perror("Failed to allocate memory for details");
      exit(EXIT_FAILURE);
    }

    for (int j = 0; j < flags.arrLength; j++) {
      generateRandomString(arrDetails[i][j].id, ID_LENGTH);
      generateRandomString(arrDetails[i][j].name, rand() % MAX_NAME_SIZE + 1);
      arrDetails[i][j].count = rand() % 100;
    }
  }

  return arrDetails;
}

void generateRandomString(char *str, int length) {
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  for (int i = 0; i < length; i++) {
    int index = rand() % (sizeof(charset) - 1);
    str[i] = charset[index];
  }
  str[length] = '\0';
}