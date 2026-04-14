#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "../utils/utils.h"

int input(Flags flags, Detail **details);

int stdInput(Detail **details);
int textFileInput(char *inputFile, Detail **details);
int binFileInput(char *inputFile, Detail **details);

void output(Flags flags, Detail *details, int length);

void stdOutput(Detail *details, int length);
void textFileOutput(char *outputFile, Detail *details, int length);
void binFileOutput(char *outputFile, Detail *details, int length);

#endif