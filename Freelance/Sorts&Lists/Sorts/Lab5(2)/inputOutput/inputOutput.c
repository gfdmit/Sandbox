#include "inputOutput.h"

int input(Flags flags, Detail **details) {
  int length;
  if (strcmp(flags.inputType, "stdin") == 0) {
    length = stdInput(details);
  } else if (strcmp(flags.inputType, "text") == 0) {
    if (flags.inputFile == NULL) {
      fprintf(stderr, "Input file not specified for text input type\n");
      return 0;
    }
    length = textFileInput(flags.inputFile, details);
  } else if (strcmp(flags.inputType, "binary") == 0) {
    if (flags.inputFile == NULL) {
      fprintf(stderr, "Input file not specified for binary input type\n");
      return 0;
    }
    length = binFileInput(flags.inputFile, details);
  } else {
    fprintf(stderr, "Invalid input type\n");
    return 0;
  }
  return length;
}

void output(Flags flags, Detail *details, int length) {
  if (strcmp(flags.outputFormat, "stdout") == 0) {
    stdOutput(details, length);
  } else if (strcmp(flags.outputFormat, "text") == 0) {
    if (flags.outputFile == NULL) {
      fprintf(stderr, "Output file not specified for text output format\n");
      return;
    }
    textFileOutput(flags.outputFile, details, length);
  } else if (strcmp(flags.outputFormat, "binary") == 0) {
    if (flags.outputFile == NULL) {
      fprintf(stderr, "Output file not specified for binary output format\n");
      return;
    }
    binFileOutput(flags.outputFile, details, length);
  } else {
    fprintf(stderr, "Invalid output format\n");
    return;
  }
}

int stdInput(Detail **details) {
  *details = malloc(sizeof(Detail));
  if (*details == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    return 0;
  }

  char *string = calloc(MAX_LENGTH, sizeof(char));
  if (string == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    free(string);
    return 0;
  }

  int detailCount = 0;

  while (fscanf(stdin, "%[^\n]\n", string) != EOF) {
    (*details)[detailCount] = parseString(string);
    if (strcmp((*details)[detailCount].id, "") != 0) {
      detailCount++;
      Detail *temp = realloc(*details, sizeof(Detail) * (detailCount + 1));
      if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(string);
        return 0;
      }
      *details = temp;
    }
    memset(string, '\0', MAX_LENGTH);
  }

  free(string);

  return detailCount;
}

int textFileInput(char *inputFile, Detail **details) {
  FILE *file = fopen(inputFile, "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file\n");
    return 0;
  }

  *details = malloc(sizeof(Detail));
  if (*details == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(file);
    return 0;
  }

  char *string = calloc(MAX_LENGTH, sizeof(char));
  if (string == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(file);
    return 0;
  }

  int detailCount = 0;

  while (fscanf(file, "%[^\n]\n", string) != EOF) {
    (*details)[detailCount] = parseString(string);
    if (strcmp((*details)[detailCount].id, "") != 0) {
      detailCount++;
      Detail *temp = realloc(*details, sizeof(Detail) * (detailCount + 1));
      if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(string);
        fclose(file);
        return 0;
      }
      *details = temp;
    }
    memset(string, '\0', MAX_LENGTH);
  }

  free(string);

  fclose(file);
  return detailCount;
}

int binFileInput(char *inputFile, Detail **details) {
  FILE *file = fopen(inputFile, "rb");
  if (file == NULL) {
    perror("Ошибка открытия файла");
    return 0;
  }

  *details = malloc(sizeof(Detail));
  if (*details == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(file);
    return 0;
  }

  int detailCount = 0;

  char buffer[MAX_LENGTH];
  size_t bytesRead = 0;

  while ((bytesRead = fread(buffer, 1, MAX_LENGTH - 1, file)) > 0) {
    buffer[bytesRead] = '\0';

    char *lastNewline = NULL;
    if (bytesRead == MAX_LENGTH - 1) {
      lastNewline = strrchr(buffer, '\n');
    }
    if (lastNewline) {
      size_t remainingBytes = (buffer + bytesRead) - (lastNewline + 1);
      fseek(file, -remainingBytes, SEEK_CUR);
      memset(lastNewline, '\0', remainingBytes + 1);
    } else {
      memset(buffer + bytesRead, '\0', MAX_LENGTH - bytesRead);
    }

    char *ptrInBuffer = buffer;
    char *line = strtok(ptrInBuffer, "\n");
    while (line != NULL) {
      ptrInBuffer += strlen(line) + 1;
      (*details)[detailCount] = parseString(line);
      if (strcmp((*details)[detailCount].id, "") != 0) {
        detailCount++;
        Detail *temp = realloc(*details, sizeof(Detail) * (detailCount + 1));
        if (temp == NULL) {
          fprintf(stderr, "Memory allocation error\n");
          fclose(file);
          return 0;
        }
        *details = temp;
      }
      line = strtok(ptrInBuffer, "\n");
    }
  }

  fclose(file);
  return detailCount;
}

void stdOutput(Detail *details, int length) {
  for (int i = 0; i < length; i++) {
    fprintf(stdout, "%s;%s;%d\n", details[i].id, details[i].name,
            details[i].count);
  }
}

void textFileOutput(char *outputFile, Detail *details, int length) {
  FILE *file = fopen(outputFile, "w");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file\n");
    return;
  }

  for (int i = 0; i < length; i++) {
    fprintf(file, "%s;%s;%d\n", details[i].id, details[i].name,
            details[i].count);
  }

  fclose(file);
}

void binFileOutput(char *outputFile, Detail *details, int length) {
  FILE *file = fopen(outputFile, "wb");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file\n");
    return;
  }

  for (int i = 0; i < length; i++) {
    char buffer[ID_LENGTH + MAX_NAME_SIZE + 50];
    snprintf(buffer, sizeof(buffer), "%s;%s;%d\n", details[i].id,
             details[i].name, details[i].count);
    fwrite(buffer, sizeof(char), strlen(buffer), file);
  }

  fclose(file);
}