#include "Renderer.h"

bool Renderer::bInitialized = false;
S2D_Window* Renderer::pWindow = NULL;

void Renderer::Init()
{
    pWindow = S2D_CreateWindow("Dungeon Generation", 640, 480, NULL, &Renderer::Render, S2D_STRETCH);
    bInitialized = true;
    S2D_Show(pWindow);
}

void Renderer::Destroy()
{
    if (bInitialized)
    {
        S2D_FreeWindow(pWindow);
        pWindow = NULL;
        bInitialized = false;
    }
}

void Renderer::Render()
{
    S2D_DrawTriangle(
        320, 50, 1, 0, 0, 1,
        540, 430, 0, 1, 0, 1,
        100, 430, 0, 0, 1, 1);
}
