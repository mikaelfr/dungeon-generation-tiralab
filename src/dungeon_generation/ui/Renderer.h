#pragma once

#include <simple2d.h>
#include "../data/Array.h"
#include "../data/Room.h"

// Currently the way Renderer and Generator are talking is mega dumb
// since Renderer is static so it's easier to pass function pointers to c funtions.
// Since this is really only used for debugging and generator will never need to talk
// to this renderer after this course, I'm just taking the easy way out and assuming
// that there will only ever be one Generator using the Renderer.
class Renderer
{
public:
    static void Init(class Generator* pGenerator);
    static void Update();
    static void Destroy();

    static void SetHeadless(bool headless);
    static void SetRoomArray(Array<Room>* rooms);
    static void SetGenerator(class Generator* pGenerator);

private:
    static int windowWidth;
    static int windowHeight;
    static bool bInitialized;
    static bool bHeadless;
    static S2D_Window* pWindow;
    static Array<Room>* pRooms;
    static class Generator* pGenerator;

    static void Render();

    // We out here going all static class and shit
    Renderer() {}
    ~Renderer() {}
};
