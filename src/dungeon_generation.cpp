// dungeon-generation.cpp : Defines the entry point for the application.
//

#include "dungeon_generation.h"
#include "dungeon_generation/Generator.h"
#include "dungeon_generation/ui/Renderer.h"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (strcmp("--headless", argv[1]) == 0)
        {
            Renderer::SetHeadless(false);
        }
    }

    Generator g;
    g.Generate(0xBEEF);

    int a;
    std::cin >> a;
    return 0;
}
