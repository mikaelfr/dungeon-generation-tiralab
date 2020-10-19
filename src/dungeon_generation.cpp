// dungeon-generation.cpp : Defines the entry point for the application.
//

#include "dungeon_generation.h"
#include "dungeon_generation/Generator.h"
#include "dungeon_generation/ui/Renderer.h"

int main(int argc, char** argv)
{
    bool bHeadless = false;
    if (argc > 1)
    {
        if (strcmp("--headless", argv[1]) == 0)
        {
            bHeadless = true;
            Renderer::SetHeadless(true);
        }
    }

    Generator g;
    g.Generate(0xBEEF, bHeadless);
    return 0;
}
