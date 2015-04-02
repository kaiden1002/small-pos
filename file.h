#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int getTill(const char *file);
void saveTill(const char *file, int till);

#endif