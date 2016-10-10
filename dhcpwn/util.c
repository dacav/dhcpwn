#include "util.h"
#include "logging.h"
#include <stdlib.h>

double random_real(double min, double max)
{
    return (min + max * rand()) / RAND_MAX;
}

uint8_t random_uint8()
{
    return random_real(0, 255);
}

void random_bytes(uint8_t *dst, size_t size)
{
    for (int i = 0; i < size; i ++) {
        dst[i] = random_uint8();
    }
}
