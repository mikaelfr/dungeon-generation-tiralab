// dungeon-generation.cpp : Defines the entry point for the application.
//

#include "dungeon_generation.h"
#include "dungeon_generation/Generator.h"
#include "dungeon_generation/ui/Renderer.h"
#include <cstring>

int main(int argc, char** argv)
{
    bool bHeadless = false;
    if (argc > 2)
    {
        if (strcmp("--headless", argv[2]) == 0)
        {
            bHeadless = true;
            Renderer::SetHeadless(true);
        }
    }

    Generator g;
    g.Generate(atoi(argv[1]), bHeadless);
    return 0;
}
