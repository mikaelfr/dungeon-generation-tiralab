#include "Renderer.h"

#include "../util/Random.h"

bool Renderer::bInitialized = false;
bool Renderer::bHeadless = false;
S2D_Window* Renderer::pWindow = NULL;
Array<Room>* Renderer::pRooms = NULL;

void Renderer::Init()
{
    if (bHeadless)
        return;

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

void Renderer::SetHeadless(bool headless)
{
    bHeadless = headless;
}

void Renderer::SetRoomArray(Array<Room>* rooms)
{
    pRooms = rooms;
}

void Renderer::Render()
{
    if (pRooms)
    {
        for (const Room& room : *pRooms)
        {
            Array<Vec2i> vertices = room.GetVertices(20);
            S2D_DrawQuad(
                vertices[0].x, vertices[0].y, Random::GetRandomValue(), Random::GetRandomValue(), Random::GetRandomValue(), 1.0f,
                vertices[1].x, vertices[1].y, Random::GetRandomValue(), Random::GetRandomValue(), Random::GetRandomValue(), 1.0f,
                vertices[2].x, vertices[2].y, Random::GetRandomValue(), Random::GetRandomValue(), Random::GetRandomValue(), 1.0f,
                vertices[3].x, vertices[3].y, Random::GetRandomValue(), Random::GetRandomValue(), Random::GetRandomValue(), 1.0f);
        }
    }
}
