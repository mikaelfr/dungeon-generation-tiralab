#include "Random.h"
#include <ctime>

// Initialize static member variables
unsigned int Random::index = n + 1;
unsigned int Random::mt[n];

/*
Sets the seed for the Mersenne Twister algorithm

@param seed Seed to use in the algorithm
*/
void Random::SetSeed(unsigned int seed)
{
    index = n;
    mt[0] = seed;
    for (unsigned int i = 1; i < n; i++)
    {
        mt[i] = f * (mt[i - 1] ^ (mt[i - 1] >> (w - 2))) + i;
    }
}

/*
Returns a normalized pseudorandom float between 0.0 and 1.0

@return Pseudorandom float between 0.0 and 1.0
*/
float Random::GetRandomValue()
{
    return (float)GetRandomNumber() / d;
}

/*
Returns a new pseudorandom number between 0 and d
using the Mersenne Twister algorithm

@return Pseudorandom unsigned int between 0 and d
*/
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

/*
Generates a new set of n pseudorandom numbers
*/
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
