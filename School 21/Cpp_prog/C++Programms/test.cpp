#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
// int getopt_long(int argc, char *const argv[],
// const char *optstring,
// const struct option *longopts, int *longindex);

typedef struct {
  bool NotEmptyNonBlank;
  bool StringCharactersLike;
  bool NumbersTheOutputLines;
  bool SqueezeEmptyLines;
  bool DisplaysTabsAsI;
  bool ASCII;
} Flags;

Flags CatReadFlags(int argc, char *argv[]) {
  struct option longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};

  int currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL);
  Flags flags = {false, false, false, false, false, false};
  for (; currentFlag != -1;
       currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL)) {
    switch (currentFlag) {
      case 'b':
        flags.NotEmptyNonBlank = true;
        break;
      case 'e':
        flags.StringCharactersLike = true;
        flags.ASCII = true;
        break;
      case 'E':
        flags.StringCharactersLike = true;
        break;
      case 'n':
        flags.NumbersTheOutputLines = true;
        break;
      case 's':
        flags.SqueezeEmptyLines = true;
        break;
      case 't':
        flags.DisplaysTabsAsI = true;
        flags.ASCII = true;
        break;
      case 'T':
        flags.DisplaysTabsAsI = true;
        break;
      case 'v':
        flags.ASCII = true;
        break;
    }
  }
  return flags;
}

int calling_flags_and_parser(char *filename, Flags flags) {
  int strCounter = 1;
  FILE *file = fopen(filename, "r+");
  if (file == NULL) {
    printf("Failed to open file");
    return 0;
  }
  int c = fgetc(file);
  int prev = '\n';
  while (c != EOF) {
    if (flags.NotEmptyNonBlank == true && c != '\n' &&
        prev == '\n') {  //нумерует только непустые строки -b
      printf("\n%d.", strCounter);
      strCounter++;
    } else if (flags.NumbersTheOutputLines == true &&
               flags.NotEmptyNonBlank == false &&
               prev == '\n') {  //нумерует все выходные строки -n
      printf("%d ", strCounter);
      strCounter++;
    } else if (flags.ASCII == true) {
      if (c >= 128 && c <= 159) {
        printf("%s", "M-^");
        c = c - 64;
      } else if (c >= 0 && c <= 31 && c != 9 && c != 10) {
        printf("%c", '^');
        c = c + 64;
      } else if (c == 127) {
        printf("%c", '^');
        c = '?';
      } else if (c >= 160 && c <= 254) {
        printf("%s", "M-");
        c = c - 128;
      } else if (c == 255) {
        printf("%s", "M-^");
        c = '?';
      }
    }
    printf("%c", c);
    prev = c;
    c = fgetc(file);
  }

  fclose(file);
  return 0;
}

int main(int argc, char *argv[]) {
  Flags flags = CatReadFlags(argc, argv);
  printf("%d,%d,%d,%d,%d,\n", flags.NotEmptyNonBlank,
         flags.StringCharactersLike, flags.NumbersTheOutputLines,
         flags.SqueezeEmptyLines, flags.DisplaysTabsAsI);
  calling_flags_and_parser(argv[optind], flags);
}