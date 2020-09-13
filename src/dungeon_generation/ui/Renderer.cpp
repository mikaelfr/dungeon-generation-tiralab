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

void Renderer::Init(Generator* pGenerator)
{
    if (bHeadless)
        return;

    Renderer::pGenerator = pGenerator;
    pWindow = S2D_CreateWindow("Dungeon Generation", windowWidth, windowHeight, &Renderer::Update, &Renderer::Render, S2D_STRETCH);
    pWindow->background = S2D_Color{ 0.925f, 0.957f, 0.957f, 1.0f };
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
    int halfWidth = windowWidth / 2;
    int halfHeight = windowHeight / 2;
    if (pRooms)
    {
        for (const Room& room : *pRooms)
        {
            Array<Vec2i> vertices = room.GetVertices();
            S2D_DrawQuad(
                (GLfloat)vertices[0].x + halfWidth, (GLfloat)vertices[0].y + halfHeight, 0.0f, 0.415f, 0.443f, 1.0f,
                (GLfloat)vertices[1].x + halfWidth, (GLfloat)vertices[1].y + halfHeight, 0.0f, 0.415f, 0.443f, 1.0f,
                (GLfloat)vertices[2].x + halfWidth, (GLfloat)vertices[2].y + halfHeight, 0.0f, 0.415f, 0.443f, 1.0f,
                (GLfloat)vertices[3].x + halfWidth, (GLfloat)vertices[3].y + halfHeight, 0.0f, 0.415f, 0.443f, 1.0f);

            S2D_DrawLine(
                (GLfloat)vertices[0].x + halfWidth, (GLfloat)vertices[0].y + halfHeight, (GLfloat)vertices[1].x + halfWidth, (GLfloat)vertices[1].y + halfHeight, 1.0f, 
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
            S2D_DrawLine(
                (GLfloat)vertices[1].x + halfWidth, (GLfloat)vertices[1].y + halfHeight, (GLfloat)vertices[2].x + halfWidth, (GLfloat)vertices[2].y + halfHeight, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
            S2D_DrawLine(
                (GLfloat)vertices[2].x + halfWidth, (GLfloat)vertices[2].y + halfHeight, (GLfloat)vertices[3].x + halfWidth, (GLfloat)vertices[3].y + halfHeight, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
            S2D_DrawLine(
                (GLfloat)vertices[3].x + halfWidth, (GLfloat)vertices[3].y + halfHeight, (GLfloat)vertices[0].x + halfWidth, (GLfloat)vertices[0].y + halfHeight, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
}
