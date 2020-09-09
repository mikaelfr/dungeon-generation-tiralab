// dungeon-generation.cpp : Defines the entry point for the application.
//

#include "dungeon_generation.h"
#include "dungeon_generation/util/Math.h"
#include "dungeon_generation/util/Random.h"

using namespace std;

int main()
{
	Random::SetSeed(0xBEEF);

	for (int i = 0; i < 10; i++)
	{
		cout << Random::GetRandomValue() << endl;
	}

	int a;
	cin >> a;
	return 0;
}
