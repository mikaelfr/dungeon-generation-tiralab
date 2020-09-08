#pragma once

class Random
{
public:
	// Sets the seed for the algorithm
	// Prepares mt for twisting
	static void SetSeed(int seed);

	static float GetRandomValue();

private:
	// Default parameters for MT19937
	static const int w = 32;
	static const int n = 624;
	static const int m = 397;
	static const int r = 31;
	static const int a = 0x9908B0DF;
	static const int u = 11;
	static const int d = 0xFFFFFFFF;
	static const int s = 7;
	static const int b = 0x9D2C5680;
	static const int t = 15;
	static const int c = 0xEFC60000;
	static const int l = 18;
	static const int f = 1812433253;
	static const int lower_mask = ~(1 << r);
	static const int upper_mask = ~lower_mask;

	static int mt[n];
	static int index;

	// Returns a new random number from mt
	// Sets seed if needed
	// Generates new set of n random numbers if needed
	static int GetRandomNumber();

	// Generates a new set of n random numbers
	static void Twist();

	// Disallow creating instances
	Random() {};
	~Random() {};
};
