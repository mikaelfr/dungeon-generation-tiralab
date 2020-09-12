#pragma once

#include <simple2d.h>

class Renderer
{
public:
    static void Init();
    static void Destroy();

private:
    static bool bInitialized;
    static S2D_Window* pWindow;

    static void Render();

    // We out here going all static class and shit
    Renderer() {}
    ~Renderer() {}
};
