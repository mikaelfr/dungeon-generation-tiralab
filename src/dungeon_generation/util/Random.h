#pragma once

class Random
{
public:
    // Sets the seed for the algorithm
    // Prepares mt for twisting
    static void SetSeed(unsigned int seed);

    static float GetRandomValue();

private:
    // Default parameters for MT19937
    static const unsigned int w = 32;
    static const unsigned int n = 624;
    static const unsigned int m = 397;
    static const unsigned int r = 31;
    static const unsigned int a = 0x9908B0DF;
    static const unsigned int u = 11;
    static const unsigned int d = 0xFFFFFFFF;
    static const unsigned int s = 7;
    static const unsigned int b = 0x9D2C5680;
    static const unsigned int t = 15;
    static const unsigned int c = 0xEFC60000;
    static const unsigned int l = 18;
    static const unsigned int f = 1812433253;
    static const unsigned int lower_mask = ~(1 << r);
    static const unsigned int upper_mask = ~lower_mask;

    static unsigned int mt[n];
    static unsigned int index;

    // Returns a new random number from mt
    // Sets seed if needed
    // Generates new set of n random numbers if needed
    static unsigned int GetRandomNumber();

    // Generates a new set of n random numbers
    static void Twist();

    // Disallow creating instances
    Random() {};
    ~Random() {};
};
