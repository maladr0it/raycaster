#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

void *safe_malloc(size_t size);
double mod(double val, double upper);
double clamp(double val, double lower, double upper);

#endif