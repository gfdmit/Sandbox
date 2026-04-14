#include "sorting.h"

void sort(Flags flags, Detail **details, int length) {
  int sorting;
  int field;
  int direction;

  static void (*sortings[3])(void *details, size_t length, size_t size,
                             int (*compare)(const void *, const void *)) = {
      gnomeSort, heapSort, qsort};
  static int (*comparators[6])(const void *a, const void *b) = {
      compareByIdAsc,  compareByNameAsc,  compareByCountAsc,
      compareByIdDesc, compareByNameDesc, compareByCountDesc};

  if (strcmp(flags.sorting, "gnome") == 0) {
    sorting = 0;
  } else if (strcmp(flags.sorting, "heap") == 0) {
    sorting = 1;
  } else if (strcmp(flags.sorting, "quick") == 0) {
    sorting = 2;
  } else {
    fprintf(stderr, "Wrong sorting algorithm\n");
    return;
  }

  if (strcmp(flags.field, "id") == 0) {
    field = 0;
  } else if (strcmp(flags.field, "name") == 0) {
    field = 1;
  } else if (strcmp(flags.field, "count") == 0) {
    field = 2;
  } else {
    fprintf(stderr, "Wrong stucture field\n");
    return;
  }

  if (strcmp(flags.direction, "desc") == 0) {
    direction = 1;
  } else if (strcmp(flags.direction, "asc") == 0) {
    direction = 0;
  } else {
    fprintf(stderr, "Wrong direction\n");
    return;
  }

  sortings[sorting](*details, length, sizeof(Detail),
                    comparators[field + 3 * direction]);
}

int compareByIdAsc(const void *a, const void *b) {
  Detail *detailA = (Detail *)a;
  Detail *detailB = (Detail *)b;
  return strcmp(detailA->id, detailB->id);
}

int compareByNameAsc(const void *a, const void *b) {
  Detail *detailA = (Detail *)a;
  Detail *detailB = (Detail *)b;
  return strcmp(detailA->name, detailB->name);
}

int compareByCountAsc(const void *a, const void *b) {
  Detail *detailA = (Detail *)a;
  Detail *detailB = (Detail *)b;
  return detailA->count - detailB->count;
}

int compareByIdDesc(const void *a, const void *b) {
  Detail *detailA = (Detail *)a;
  Detail *detailB = (Detail *)b;
  return 0 - strcmp(detailA->id, detailB->id);
}

int compareByNameDesc(const void *a, const void *b) {
  Detail *detailA = (Detail *)a;
  Detail *detailB = (Detail *)b;
  return 0 - strcmp(detailA->name, detailB->name);
}

int compareByCountDesc(const void *a, const void *b) {
  Detail *detailA = (Detail *)a;
  Detail *detailB = (Detail *)b;
  return 0 - (detailA->count - detailB->count);
}

void swap(Detail *a, Detail *b) {
  Detail temp = *a;
  *a = *b;
  *b = temp;
}

void gnomeSort(void *ptr, size_t length, size_t size,
               int (*compare)(const void *, const void *)) {
  Detail *details = (Detail *)ptr;
  int index = 0;

  while (index < length) {
    if (index == 0) {
      index++;
    }
    if (compare((void *)&details[index], (void *)&details[index - 1]) >= 0) {
      index++;
    } else {
      swap(&details[index], &details[index - 1]);
      index--;
    }
  }
}

void heapify(void *ptr, size_t length, int i,
             int (*compare)(const void *, const void *)) {
  Detail *details = (Detail *)ptr;
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < length && compare(&details[left], &details[largest]) >= 0)
    largest = left;

  if (right < length && compare(&details[right], &details[largest]) >= 0)
    largest = right;

  if (largest != i) {
    swap(&details[i], &details[largest]);
    heapify(details, length, largest, compare);
  }
}

void heapSort(void *ptr, size_t length, size_t size,
              int (*compare)(const void *, const void *)) {
  Detail *details = (Detail *)ptr;
  for (int i = length / 2 - 1; i >= 0; i--)
    heapify(details, length, i, compare);

  for (int i = length - 1; i > 0; i--) {
    swap(&details[0], &details[i]);
    heapify(details, i, 0, compare);
  }
}