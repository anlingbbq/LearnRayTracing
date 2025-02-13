#ifndef RANDOM
#define RANDOM

static unsigned long long seed = 1;

float drand48()
{
    seed = (0x5DEECE66DLL * seed + 0xB16) & 0xFFFFFFFFFFFFLL;
    unsigned long long x = seed >> 16;
    return  (float)((double)x / (double)0x100000000LL);
}

void srand48(unsigned int i)
{
    seed = (((long long int)i) << 16) | rand();
}

#endif
