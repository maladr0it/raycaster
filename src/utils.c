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

int min_int(int val1, int val2)
{
    return val1 < val2 ? val1 : val2;
}

int min_double(double val1, double val2)
{
    return val1 < val2 ? val1 : val2;
}

int clamp_int(int val, int lower, int upper)
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

double clamp_double(double val, double lower, double upper)
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