#ifndef RECONSTRUCTED_CIRCUITSAT_H
#define RECONSTRUCTED_CIRCUITSAT_H

#include <stdint.h>

static int circuit_value(int n, uint64_t mask)
{
    int value = 1;
    for (int i = 0; i < n - 2; i += 2) {
        const int a = (int)((mask >> i) & UINT64_C(1));
        const int b = (int)((mask >> (i + 1)) & UINT64_C(1));
        const int c = (int)((mask >> (i + 2)) & UINT64_C(1));
        value = value && (a || b) && (!b || !c);
    }
    return value;
}

#endif

