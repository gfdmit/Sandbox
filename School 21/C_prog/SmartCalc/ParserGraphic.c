#include "parser.h"

void graphicParser(char *str, double x1, double x2, double *Yposes) {
    char *str1 = NULL;
    char *strToModify = NULL;
    strToModify = (char *)calloc(1024, sizeof(char));
    double step = (x2 - x1) / 200;
    char doubleStr[100], newStr[1024] = {};
    for (int counter = 0; x1 <= x2; x1 += step, counter++) {
        sprintf(doubleStr, "%f", x1);
        strcat(strToModify, str);
        str1 = strtok(strToModify, "x");
        if (str[0] == 'x') {
            if (x1 >= 0) {
                strcat(newStr, doubleStr);
            } else {
                strcat(newStr, "(");
                strcat(newStr, doubleStr);
                strcat(newStr, ")");
            }
        }
        while (str1 != NULL) {
            strcat(newStr, str1);
            str1 = strtok(NULL, "x");
            if (str1 != NULL || str[strlen(str) - 1] == 'x') {
                if (x1 >= 0) {
                    strcat(newStr, doubleStr);
                } else {
                    strcat(newStr, "(");
                    strcat(newStr, doubleStr);
                    strcat(newStr, ")");
                }
            }
        }
        Yposes[counter] = parser(newStr);
        memset(strToModify, 0, strlen(strToModify));
        memset(newStr, 0, sizeof(newStr));
    }
    free(strToModify);
}
