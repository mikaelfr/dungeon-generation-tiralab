#pragma once

#include <simple2d.h>
#include "../data/Array.h"
#include "../data/Room.h"
#include "../data/Triangle.h"

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
    static void SetRoomArray(Array<std::shared_ptr<Room>>* pRooms, Array<std::shared_ptr<Triangle>>* pTriangles, Array<Edge>* pSelectedEdges, Array<Tuple<Vec2, Vec2>>* pLines);
    static void SetGenerator(class Generator* pGenerator);

private:
    static int windowWidth;
    static int windowHeight;
    static bool bInitialized;
    static bool bHeadless;
    static S2D_Window* pWindow;
    static Array<std::shared_ptr<Room>>* pRooms;
    static Array<std::shared_ptr<Triangle>>* pTriangles;
    static Array<Edge>* pSelectedEdges;
    static Array<Tuple<Vec2, Vec2>>* pLines;
    static class Generator* pGenerator;

    static S2D_Color bgColor;
    static S2D_Color fgColor;
    static S2D_Color hgColor;
    static S2D_Color hgHallColor;

    static void Render();

    // We out here going all static class and shit
    Renderer() {}
    ~Renderer() {}
};
