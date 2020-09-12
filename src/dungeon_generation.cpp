// dungeon-generation.cpp : Defines the entry point for the application.
//

#include "dungeon_generation.h"
#include "dungeon_generation/Generator.h"

int main()
{
    Generator g;
    g.Generate(0xBEEF);

    int a;
    std::cin >> a;
    return 0;
}
