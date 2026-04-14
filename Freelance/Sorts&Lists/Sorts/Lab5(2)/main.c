#include "inputOutput/inputOutput.h"
#include "sorting/sorting.h"
#include "utils/utils.h"
#include <bits/getopt_core.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Flags flags = parseFlags(argc, argv);
  Detail *details = NULL;
  int length = 0;

  if (flags.inputType == NULL || flags.outputFormat == NULL ||
      flags.sorting == NULL || flags.field == NULL || flags.direction == NULL) {
    printUsage();
    return EXIT_FAILURE;
  }

  length = input(flags, &details);
  sort(flags, &details, length);
  output(flags, details, length);

  free(details);
}