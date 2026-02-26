#include "parser.h"

int findPriority(int index) {
    if (index >= 1 && index <= 2) {
        return 1;
    } else if (index >= 3 && index <= 5) {
        return 2;
    } else if (index == 6) {
        return 3;
    } else if (index >= 9 && index <= 17) {
        return 4;
    } else if (index == -1) {
        return 0;
    } else {
        return 5;
    }
}

int checkOperators(char symb) {
    if (symb == '-') return 1;
    if (symb == '+') return 2;
    if (symb == '*') return 3;
    if (symb == '/') return 4;
    if (symb == '^') return 6;
    if (symb == '(') return 7;
    if (symb == ')') return 8;
    return 0;
}

int checkFunctions(char* str) {
    if (strcmp(str, "sin") == 0) return 9;
    if (strcmp(str, "cos") == 0) return 10;
    if (strcmp(str, "tan") == 0) return 11;
    if (strcmp(str, "asin") == 0) return 12;
    if (strcmp(str, "acos") == 0) return 13;
    if (strcmp(str, "atan") == 0) return 14;
    if (strcmp(str, "sqrt") == 0) return 15;
    if (strcmp(str, "ln") == 0) return 16;
    if (strcmp(str, "log") == 0) return 17;
    if (strcmp(str, "mod") == 0) return 5;
    return 0;
}

int checkPriority(int_stack* stack, char* str) {
    int top = int_stack_top(stack);
    int topPriority = findPriority(top);
    int strPriority = 0;
    if (strlen(str) == 1) {
        strPriority = findPriority(checkOperators(str[0]));
    } else {
        strPriority = findPriority(checkFunctions(str));
    }
    if (top == 7) {
        return 0;
    } else if (str[0] == ')') {
        return 1;
    } else if (topPriority >= strPriority) {
        return 1;
    } else {
        return 0;
    }
}

int isFunction(int index) {
    return (index >= 9 && index <= 17) ? 1 : 0;
}

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

void performOperation(double_stack** stack_operands, int_stack** stack_operators) {
    double ans = 0;
    if (isFunction(int_stack_top(*stack_operators))) {
        double operand;
        int function;
        if (int_stack_top(*stack_operators) != -1) {
            function = int_stack_top(*stack_operators);
        } else {
            fprintf(stderr, "incorrect input\n");
            // exit(-1);
            
        }
        if (double_stack_top(*stack_operands) != -1) {
            operand = double_stack_top(*stack_operands);
        } else {
            fprintf(stderr, "incorrect input\n");
            // exit(-1);
        }
        int_stack_pop(stack_operators);
        double_stack_pop(stack_operands);
        ans = doFunction(operand, function);
        double_stack_push(stack_operands, ans);
    } else {
        double operand1;
        double operand2;
        int operation;
        if (int_stack_top(*stack_operators) != -1) {
            operation = int_stack_top(*stack_operators);
        } else {
            fprintf(stderr, "incorrect input\n");
            // exit(-1);
        }
        if (double_stack_top(*stack_operands) != -1.212121) {
            operand1 = double_stack_top(*stack_operands);
        } else {
            fprintf(stderr, "incorrect input\n");
            // exit(-1);
        }
        int_stack_pop(stack_operators);
        double_stack_pop(stack_operands);
        if (double_stack_top(*stack_operands) != -1.212121) {
            operand2 = double_stack_top(*stack_operands);
        } else {
            fprintf(stderr, "incorrect input\n");
            // exit(-1);
        }
        double_stack_pop(stack_operands);
        ans = doOperation(operand1, operand2, operation);
        double_stack_push(stack_operands, ans);
    }
}

void lastNumberToStack(double* number, double_stack** stack) {
    double_stack_push(stack, *number);
    *number = 0;
}

void lastStrToStack(char* str, int_stack** stack) {
    if (checkFunctions(str) != 0) {
            int_stack_push(stack, checkFunctions(str));
    } else {
            fprintf(stderr, "incorrect input\n");
            memset(str, 0, sizeof(str));
            // exit(-1);
    }
    memset(str, 0, sizeof(str));
}

double parser(char* str) {
    int str_index = 0;
    int charFlag = 0;
    int zeroFlag = 0;
    int pointFlag = 0;
    double tempNumber = 0;
    char tempStr[100] = {};
    double_stack* stack_operands = NULL;
    int_stack* stack_operators = NULL;
    if (str[str_index] == '-' || str[str_index] == '+') {
        double_stack_push(&stack_operands, 0);
    }
    while (str[str_index] != '\0') {
        if (str[str_index] == '.') {
            if ((tempNumber != 0 || zeroFlag) && !pointFlag) {
                pointFlag = 1;
                str_index++;
                continue;
            } else {
                fprintf(stderr, "incorrect input\n");
                // exit(-1);
            }
        }
        if (isdigit(str[str_index]) || str[str_index] == '.') {
            if (zeroFlag && !pointFlag) {
                fprintf(stderr, "incorrect input\n");
                // exit(-1);
            }
            if (pointFlag) {
                tempNumber = tempNumber + (str[str_index]-48) / pow(10, pointFlag);
            } else {
                tempNumber = tempNumber * 10 + (str[str_index]-48);
                if (str[str_index] == '0' && tempNumber == 0) zeroFlag = 1;
            }
        } else if (isalpha(str[str_index])) {
            tempStr[strlen(tempStr)] = str[str_index];
        } else if (str[str_index] != '.') {
            charFlag = 1;
        }

        if ((tempNumber != 0 || zeroFlag == 1) && (!isdigit(str[str_index]) || str[str_index] == '.')) {
            double_stack_push(&stack_operands, tempNumber);
            tempNumber = 0;
            zeroFlag = 0;
            pointFlag = 0;
        }

        if (strlen(tempStr) != 0 && !isalpha(str[str_index])) {
            if (checkFunctions(tempStr) != 0) {
                while (checkPriority(stack_operators, tempStr)) {
                    performOperation(&stack_operands, &stack_operators);
                }
                if (int_stack_top(stack_operators) == 7 && checkFunctions(tempStr) == 5) {
                    fprintf(stderr, "incorrect input\n");
                    memset(tempStr, 0, sizeof(tempStr));
                    // exit(-1);
                }
                int_stack_push(&stack_operators, checkFunctions(tempStr));
            } else {
                fprintf(stderr, "incorrect input\n");
                memset(tempStr, 0, sizeof(tempStr));
                // exit(-1);
            }
            memset(tempStr, 0, sizeof(tempStr));
        }

        if (charFlag == 1) {
            if (checkOperators(str[str_index]) != 0) {
                char symbStr[10] = {0};
                symbStr[0] = str[str_index];
                if (str[str_index] == '(') {
                    if (str[str_index + 1] == '+' || str[str_index + 1] == '-') {
                        double_stack_push(&stack_operands, 0);
                    }
                }
                while (checkPriority(stack_operators, symbStr)) {
                    performOperation(&stack_operands, &stack_operators);
                }
                if (str[str_index] != ')') {
                    int_stack_push(&stack_operators, checkOperators(str[str_index]));
                } else {
                    int_stack_pop(&stack_operators);
                }
            } else {
                fprintf(stderr, "incorrect input\n");
                // exit(-1);
            }
            charFlag = 0;
        }
        if (pointFlag) pointFlag++;
        ++str_index;
    }
    if (tempNumber != 0 || zeroFlag == 1) lastNumberToStack(&tempNumber, &stack_operands);
    if (strlen(tempStr) != 0) lastStrToStack(tempStr, &stack_operators);
    while (int_stack_top(stack_operators) != -1) {
        performOperation(&stack_operands, &stack_operators);
    }
    return double_stack_top(stack_operands);
}
