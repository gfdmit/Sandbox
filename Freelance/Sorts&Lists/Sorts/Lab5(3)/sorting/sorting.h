#ifndef SORTING_H
#define SORTING_H

#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

int compareByIdAsc(const void *a, const void *b);
int compareByIdDesc(const void *a, const void *b);

int compareByNameAsc(const void *a, const void *b);
int compareByNameDesc(const void *a, const void *b);

int compareByCountAsc(const void *a, const void *b);
int compareByCountDesc(const void *a, const void *b);

void swap(Detail *a, Detail *b);

void gnomeSort(void *details, size_t length, size_t size,
               int (*compare)(const void *, const void *));

void heapify(void *details, size_t length, int i,
             int (*compare)(const void *, const void *));

void heapSort(void *details, size_t length, size_t size,
              int (*compare)(const void *, const void *));

void sort(Flags flags, Detail **details, int length);

#endif