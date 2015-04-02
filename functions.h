#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "file.h"

void printPrompt(int prompt);
int toString(char a[]);
int isDollarFormat(char input[]);
int isSingleDigit(char input[]);
void dollarFormat(int cents, char* output);
int centsFromCents(int cents);
int dollarsFromCents(int cents);
void addToTill(int amount, int* till, const char *file);

#endif