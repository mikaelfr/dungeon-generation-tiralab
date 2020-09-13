#pragma once

#include <simple2d.h>
#include "../data/Array.h"
#include "../data/Room.h"

class Renderer
{
public:
    static void Init();
    static void Destroy();

    static void SetHeadless(bool headless);
    static void SetRoomArray(Array<Room>* rooms);

private:
    static bool bInitialized;
    static bool bHeadless;
    static S2D_Window* pWindow;
    static Array<Room>* pRooms;

    static void Render();

    // We out here going all static class and shit
    Renderer() {}
    ~Renderer() {}
};
