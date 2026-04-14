#include "timer/timer.h"
#include "utils/utils.h"
#include <bits/getopt_core.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));
  Flags flags = parseFlags(argc, argv);
  Detail **arrDetails = NULL;

  if (flags.sorting == NULL || flags.field == NULL || flags.direction == NULL ||
      flags.arrLength == 0 || flags.arrCount == 0) {
    printUsage();
    exit(EXIT_FAILURE);
  }

  arrDetails = generate(flags);
  double delta = timer(flags, arrDetails);
  printf("%lf\n", delta);

  for (int i = 0; i < flags.arrCount; i++) {
    free(arrDetails[i]);
  }
  free(arrDetails);
}