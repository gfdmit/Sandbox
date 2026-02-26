
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "stack.h"

int findPriority(int index);
int checkOperators(char symb);
int checkFunctions(char* str);
int checkPriority(int_stack* stack, char* str);
int isFunction(int index);
double doFunction(double operand, int function);
double doOperation(double operand1, double operand2, int operation);
void performOperation(double_stack** stack_operands, int_stack** stack_operators);
void lastNumberToStack(double* number, double_stack** stack);
void lastStrToStack(char* str, int_stack** stack);
double parser(char* str);
