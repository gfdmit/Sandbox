#include "timer.h"

double timer(Flags flags, Detail **arrDetails) {
  clock_t start, end;
  start = clock();
  for (int i = 0; i != flags.arrCount; i++) {
    sort(flags, &arrDetails[i], flags.arrLength);
  }
  end = clock();
  double delta = (double)(end - start) / (double)(CLOCKS_PER_SEC);
  return delta;
}