#include "parser.h"

int findPriority(int index) {
  int retval = 0;
  if (index == -1) {
    retval = 0;
  } else if (index >= 1 && index <= 2) {
    retval = 2;
  } else if (index >= 3 && index <= 5) {
    retval = 3;
  } else if (index == 6) {
    retval = 4;
  } else if (index >= 9 && index <= 17) {
    retval = 5;
  } else {
    retval = 1;
  }
  return retval;
}

int checkToken(char* token) {
    int index = 0;
    if (strlen(token) == 1 || strcmp(token, "mod") == 0) {
        index = checkOperators(token);
    } else {
        index = checkFunctions(token);
    }
    return index;
}

int checkOperators(char* str) {
  int retval = 0;
  if (str[0] == '-') retval = 1;
  if (str[0] == '+') retval = 2;
  if (str[0] == '*') retval = 3;
  if (str[0] == '/') retval = 4;
  if (strcmp(str, "mod") == 0) retval = 5;
  if (str[0] == '^') retval = 6;
  if (str[0] == '(') retval = 7;
  if (str[0] == ')') retval = 8;
  return retval;
}

int checkFunctions(char* str) {
  int retval = 0;
  if (strcmp(str, "sin") == 0) retval = 9;
  if (strcmp(str, "cos") == 0) retval = 10;
  if (strcmp(str, "tan") == 0) retval = 11;
  if (strcmp(str, "asin") == 0) retval = 12;
  if (strcmp(str, "acos") == 0) retval = 13;
  if (strcmp(str, "atan") == 0) retval = 14;
  if (strcmp(str, "sqrt") == 0) retval = 15;
  if (strcmp(str, "ln") == 0) retval = 16;
  if (strcmp(str, "log") == 0) retval = 17;
  return retval;
}

int checkPriority(int_stack** stack, char* str) {
  int retval = 0;
  int top = int_stack_top(*stack); // -1 if stack is empty
  int topPriority = findPriority(top); // 0 if stack is empty
  int strPriority = findPriority(checkToken(str));
  if (checkToken(str) == 7) {
    retval = 0;
  } else if (checkToken(str) == 8 && top == 7) {
    int_stack_pop(stack);
  } else if (checkToken(str) == 6) {
    if (strPriority < topPriority) {
        retval = 1;
    }
  } else if (strPriority <= topPriority) {
    retval = 1;
  }
  return retval;
}

int isFunction(int index) { return (index >= 9 && index <= 17) ? 1 : 0; }

double doFunction(double operand, int function) {
  switch (function) {
    case 9:
      return sin(operand);
      break;
    case 10:
      return cos(operand);
      break;
    case 11:
      return tan(operand);
      break;
    case 12:
      return asin(operand);
      break;
    case 13:
      return acos(operand);
      break;
    case 14:
      return atan(operand);
      break;
    case 15:
      return sqrt(operand);
      break;
    case 16:
      return log(operand);
      break;
    case 17:
      return log10(operand);
      break;
    default:
      break;
  }
  return 0;
}

double doOperation(double operand1, double operand2, int operation) {
  switch (operation) {
    case 1:
      return operand2 - operand1;
      break;
    case 2:
      return operand2 + operand1;
      break;
    case 3:
      return operand2 * operand1;
      break;
    case 4:
      return operand2 / operand1;
      break;
    case 5:
      return fmod(operand2, operand1);
      break;
    case 6:
      return pow(operand2, operand1);
      break;
    default:
      break;
  }
  return 0;
}

void performFunction(double_stack** stack_operands,
                      int_stack** stack_operators, int* errorFlag) {
    double ans = 0;
    double operand = 0;
    int function = 0;
    if (int_stack_top(*stack_operators) != -1 && double_stack_top(*stack_operands) != -1.212121) {
      function = int_stack_top(*stack_operators);
      operand = double_stack_top(*stack_operands);
    } else {
      *errorFlag = 1;
    }
    if (*errorFlag == 0) {
      int_stack_pop(stack_operators);
      double_stack_pop(stack_operands);
      ans = doFunction(operand, function);
      double_stack_push(stack_operands, ans);
    }
}

void performOperation(double_stack** stack_operands,
                      int_stack** stack_operators, int* errorFlag) {
    double ans = 0;
    double operand1 = 0;
    double operand2 = 0;
    int operation = 0;
    if (int_stack_top(*stack_operators) != -1 && double_stack_top(*stack_operands) != -1.212121) {
      operation = int_stack_top(*stack_operators);
      operand1 = double_stack_top(*stack_operands);
    } else {
      *errorFlag = 1;
    }
    if (*errorFlag == 0) {
      int_stack_pop(stack_operators);
      double_stack_pop(stack_operands);
    }
    if (double_stack_top(*stack_operands) != -1.212121) {
      operand2 = double_stack_top(*stack_operands);
    } else {
      *errorFlag = 1;
    }
    if (*errorFlag == 0) {
      double_stack_pop(stack_operands);
      ans = doOperation(operand1, operand2, operation);
      double_stack_push(stack_operands, ans);
    }
}

void performAction(double_stack** stack_operands,
                      int_stack** stack_operators, int* errorFlag) {
  if (isFunction(int_stack_top(*stack_operators))) {
    performFunction(stack_operands, stack_operators, errorFlag);
  } else {
    performOperation(stack_operands, stack_operators, errorFlag);
  }
}

char* deleteDoubleSpace(char* str) {
  int trueIndex = 0;
  for (int i = 0; str[i]; ++i)
      if (!isspace(str[i]) || (i > 0 && !isspace(str[i - 1])))
          str[trueIndex++] = str[i];
  str[trueIndex] = '\0';
}

void strToStack(char* str, int* errorFlag, double_stack** stack_operands, int_stack** stack_operators) {
  char* endptr;
  char* token = strtok(str, " ");
  while (token != NULL) {
    if (strtod(token, &endptr)) {
      double_stack_push(stack_operands, strtod(token, &endptr));
    } else {
      if (checkToken(token) == 0) {
        *errorFlag = 1;
        return;
      }
      while (checkPriority(stack_operators, token)) {
          performAction(stack_operands, stack_operators, errorFlag);
      }
      if (checkToken(token) != 8) {
          int_stack_push(stack_operators, checkToken(token));
      }
    }
    token = strtok(NULL, " ");
  }
}

double parser(char* str, int* errorFlag) {
  double_stack* stack_operands = NULL;
  int_stack* stack_operators = NULL;
  double result = 0;
  char newStr[strlen(str)];

  strcpy(newStr, str);
  deleteDoubleSpace(newStr);
  strToStack(newStr, errorFlag, &stack_operands, &stack_operators);
  //
  if (*errorFlag != 1) {
    while (int_stack_top(stack_operators) != -1 && *errorFlag == 0) {
        performAction(&stack_operands, &stack_operators, errorFlag);
    }
    result = double_stack_top(stack_operands);
  }
  double_stack_pop(&stack_operands);
  while (stack_operands) {
    double_stack_pop(&stack_operands);
    *errorFlag = 1;
  }
  while (stack_operators) {
    int_stack_pop(&stack_operators);
    *errorFlag = 1;
  }
  return result;
}

int main() {
    char* st = "1890";
    int errorFlag = 0;
    double result = 0;
    result = parser(st, &errorFlag);
    printf("%lf, error: %d", result, errorFlag);
}