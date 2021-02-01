#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

void *safe_malloc(size_t size);

double mod(double val, double upper);

int min_int(int val1, int val2);

int clamp_int(int val, int lower, int upper);

#endif