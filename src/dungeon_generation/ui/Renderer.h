#pragma once

#include <simple2d.h>

class Renderer
{
public:
    static void Init();
    static void Destroy();

    static void SetHeadless(bool headless);

private:
    static bool bInitialized;
    static bool bHeadless;
    static S2D_Window* pWindow;

    static void Render();

    // We out here going all static class and shit
    Renderer() {}
    ~Renderer() {}
};
