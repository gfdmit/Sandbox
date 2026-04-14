#include "inputOutput/inputOutput.h"
#include "utils/utils.h"
#include <bits/getopt_core.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Flags flags = parseFlags(argc, argv);
  Detail *details = NULL;
  int length = 0;

  if (flags.inputType == NULL || flags.outputFormat == NULL) {
    printUsage();
    exit(EXIT_FAILURE);
  }

  length = input(flags, &details);
  output(flags, details, length);

  free(details);
}