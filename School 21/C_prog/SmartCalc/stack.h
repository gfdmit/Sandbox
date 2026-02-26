
#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct int_stack {
    int value;
    struct int_stack* next;
} int_stack, int_node;

typedef struct double_stack {
    double value;
    struct double_stack* next;
} double_stack, double_node;

int_stack** int_stack_push(int_stack** stack, int elem);
int int_stack_pop(int_stack** stack);
int int_stack_top(int_stack* stack);

double_stack** double_stack_push(double_stack** stack, double elem);
double double_stack_pop(double_stack** stack);
double double_stack_top(double_stack* stack);
