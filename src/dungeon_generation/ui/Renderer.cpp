#include "Renderer.h"
#include "Renderer.h"
#include "Renderer.h"

#include "../util/Random.h"
#include "../Generator.h"

int Renderer::windowWidth = 640;
int Renderer::windowHeight = 480;
bool Renderer::bInitialized = false;
bool Renderer::bHeadless = false;
S2D_Window* Renderer::pWindow = NULL;
Array<Room>* Renderer::pRooms = NULL;
Generator* Renderer::pGenerator = NULL;

S2D_Color Renderer::bgColor = { 0.925f, 0.957f, 0.957f, 1.0f };
S2D_Color Renderer::fgColor = { 0.0f, 0.415f, 0.443f, 1.0f };
S2D_Color Renderer::hgColor = { 1.0f, 0.494f, 0.404f, 1.0f };

void Renderer::Init(Generator* pGenerator)
{
    if (bHeadless)
        return;

    Renderer::pGenerator = pGenerator;
    pWindow = S2D_CreateWindow("Dungeon Generation", windowWidth, windowHeight, &Renderer::Update, &Renderer::Render, S2D_STRETCH);
    pWindow->background = bgColor;
    bInitialized = true;
    S2D_Show(pWindow);
}

void Renderer::Update()
{
    if (pGenerator)
        pGenerator->Update();
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

void Renderer::SetGenerator(Generator* pGenerator)
{
    Renderer::pGenerator = pGenerator;
}

void Renderer::Render()
{
    float halfWidth = (float)windowWidth / 2;
    float halfHeight = (float)windowHeight / 2;
    if (pRooms)
    {
        for (const Room& room : *pRooms)
        {
            Array<Vec2> vertices = room.GetVertices();

            S2D_Color color = fgColor;
            S2D_Color lineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

            if (room.bMainRoom)
            {
                color = hgColor;
                lineColor = { 0.95f, 0.95f, 0.95f, 1.0f };
            }

            S2D_DrawQuad(
                vertices[0].x + halfWidth, vertices[0].y + halfHeight, color.r, color.g, color.b, color.a,
                vertices[1].x + halfWidth, vertices[1].y + halfHeight, color.r, color.g, color.b, color.a,
                vertices[2].x + halfWidth, vertices[2].y + halfHeight, color.r, color.g, color.b, color.a,
                vertices[3].x + halfWidth, vertices[3].y + halfHeight, color.r, color.g, color.b, color.a);

            S2D_DrawLine(
                vertices[0].x + halfWidth, vertices[0].y + halfHeight, vertices[1].x + halfWidth, vertices[1].y + halfHeight, 1.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            S2D_DrawLine(
                vertices[1].x + halfWidth, vertices[1].y + halfHeight, vertices[2].x + halfWidth, vertices[2].y + halfHeight, 1.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            S2D_DrawLine(
                vertices[2].x + halfWidth, vertices[2].y + halfHeight, vertices[3].x + halfWidth, vertices[3].y + halfHeight, 1.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            S2D_DrawLine(
                vertices[3].x + halfWidth, vertices[3].y + halfHeight, vertices[0].x + halfWidth, vertices[0].y + halfHeight, 1.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
        }
    }
}
