#include "Random.h"
#include <ctime>

// Initialize static member variables
unsigned int Random::index = n + 1;
unsigned int Random::mt[n];


void Random::SetSeed(unsigned int seed)
{
    index = n;
    mt[0] = seed;
    for (unsigned int i = 1; i < n; i++)
    {
        mt[i] = f * (mt[i - 1] ^ (mt[i - 1] >> (w - 2))) + i;
    }
}

float Random::GetRandomValue()
{
    return (float)GetRandomNumber() / d;
}


unsigned int Random::GetRandomNumber()
{
    if (index >= n) 
    {
        if (index > n) 
        {
            // No seed set, seeding with lowest 32 bits of time(NULL)
            SetSeed((unsigned int)time(NULL));
        }
        Twist();
    }

    unsigned int y = mt[index];
    y ^= (y >> u) & d;
    y ^= (y << s) & b;
    y ^= (y << t) & c;
    y ^= y >> 1;

    index++;
    return y;
}


void Random::Twist()
{
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int x = (mt[i] & upper_mask) + (mt[(i + 1) % n] & lower_mask);
        unsigned int xA = x >> 1;
        if (x % 2 != 0)
            xA |= a;
        mt[i] = mt[(i + m) % n] ^ xA;
    }
    index = 0;
}
