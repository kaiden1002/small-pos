#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "functions.h"

int getTill(const char *file);
void saveTill(const char *file, int till);
void addSKU(int sku, int price, const char *skufile, const char *pricefile);
int getPrice(int sku, const char *skufile, const char *pricefile);
void remSKU(int sku, int price, const char *skufile, const char *pricefile);
void printSKUS(const char *skufile, const char *pricefile);

#endif