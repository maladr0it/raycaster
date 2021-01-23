#include <math.h>
#include "utils.h"

void *safe_malloc(size_t size)
{
    void *p = malloc(size);
    if (p == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return p;
}

double mod(double val, double upper)
{
    while (val < 0)
    {
        val += upper;
    }
    while (val >= upper)
    {
        val -= upper;
    }
    return val;
}

double clamp(double val, double lower, double upper)
{
    if (val < lower)
    {
        return lower;
    }
    else if (val > upper)
    {
        return upper;
    }
    else
    {
        return val;
    }
}