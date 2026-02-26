#pragma once

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int findPriority(int index);
int checkToken(char* token);
int checkOperators(char *str);
int checkFunctions(char* str);
int checkPriority(int_stack** stack, char* str);
int isFunction(int index);
double doFunction(double operand, int function);
double doOperation(double operand1, double operand2, int operation);
void performFunction(double_stack** stack_operands,
                      int_stack** stack_operators, int* errorFlag);
void performOperation(double_stack** stack_operands,
                      int_stack** stack_operators, int* errorFlag);
void performAction(double_stack** stack_operands,
                      int_stack** stack_operators, int* errorFlag);
char* deleteDoubleSpace(char* str);
void strToStack(char* str, int* errorFlag, double_stack** stack_operands, int_stack** stack_operators);
double parser(char* str, int* errorFlag);
