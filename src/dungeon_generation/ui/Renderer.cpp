#include "Renderer.h"
#include "Renderer.h"
#include "Renderer.h"
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
Array<std::shared_ptr<Room>>* Renderer::pRooms = NULL;
Array<std::shared_ptr<Triangle>>* Renderer::pTriangles = NULL;
Array<Edge>* Renderer::pSelectedEdges = NULL;
Array<Tuple<Vec2, Vec2>>* Renderer::pLines = NULL;
Generator* Renderer::pGenerator = NULL;
bool Renderer::bRunStep = false;
bool Renderer::bFinished = false;

S2D_Color Renderer::bgColor = { 0.925f, 0.957f, 0.957f, 1.0f };
S2D_Color Renderer::fgColor = { 0.0f, 0.415f, 0.443f, 1.0f };
S2D_Color Renderer::hgColor = { 1.0f, 0.494f, 0.404f, 1.0f };
S2D_Color Renderer::hgHallColor = { 0.8f, 0.1f, 0.404f, 1.0f };
S2D_Color Renderer::fgHallColor = { 0.3f, 0.3f, 0.3f, 1.0f };

void Renderer::Init(Generator* pGenerator)
{
    if (bHeadless)
        return;

    Renderer::pGenerator = pGenerator;
    pWindow = S2D_CreateWindow("Dungeon Generation", windowWidth, windowHeight, &Renderer::Update, &Renderer::Render, 0);
    pWindow->viewport.mode = S2D_STRETCH;
    pWindow->on_key = &Renderer::OnKey;
    // Turn on 8xMSAA
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
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

void Renderer::SetRoomArray(Array<std::shared_ptr<Room>>* pRooms, Array<std::shared_ptr<Triangle>>* pTriangles, Array<Edge>* pSelectedEdges, Array<Tuple<Vec2, Vec2>>* pLines)
{
    Renderer::pRooms = pRooms;
    Renderer::pTriangles = pTriangles;
    Renderer::pSelectedEdges = pSelectedEdges;
    Renderer::pLines = pLines;
}

void Renderer::SetGenerator(Generator* pGenerator)
{
    Renderer::pGenerator = pGenerator;
}

bool Renderer::ShouldRunStep()
{
    return Renderer::bRunStep;
}

void Renderer::StepRan()
{
    bRunStep = false;
}

void Renderer::SetFinished(bool bFinished)
{
    Renderer::bFinished = bFinished;
}

void Renderer::Render()
{
    float halfWidth = (float)windowWidth / 2;
    float halfHeight = (float)windowHeight / 2;

    if (pLines)
    {
        const S2D_Color red = { 1.0f, 0.0f, 0.0f, 1.0f };
        for (const Tuple<Vec2, Vec2>& l : *pLines)
        {
            /*
            S2D_DrawLine(
                l.key.x + halfWidth, l.key.y + halfHeight, l.value.x + halfWidth, l.value.y + halfHeight, 2,
                red.r, red.g, red.b, red.a,
                red.r, red.g, red.b, red.a,
                red.r, red.g, red.b, red.a,
                red.r, red.g, red.b, red.a);
                */
            const float threshold = 5.0f;
            // if horizontal
            if (Math::Abs(l.key.y - l.value.y) <= 0.01f)
            {
                if (l.key.x > l.value.x)
                {
                    S2D_DrawQuad(
                        l.key.x + halfWidth + threshold, l.key.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth - threshold, l.value.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth - threshold, l.value.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.key.x + halfWidth + threshold, l.key.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a);
                }
                else
                {
                    S2D_DrawQuad(
                        l.key.x + halfWidth - threshold, l.key.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth + threshold, l.value.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth + threshold, l.value.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.key.x + halfWidth - threshold, l.key.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a);
                }
            }
            else
            {
                if (l.key.y > l.value.y)
                {
                    S2D_DrawQuad(
                        l.key.x + halfWidth + threshold, l.key.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth + threshold, l.value.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth - threshold, l.value.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.key.x + halfWidth - threshold, l.key.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a);
                }
                else
                {
                    S2D_DrawQuad(
                        l.key.x + halfWidth + threshold, l.key.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth + threshold, l.value.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.value.x + halfWidth - threshold, l.value.y + halfHeight + threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a,
                        l.key.x + halfWidth - threshold, l.key.y + halfHeight - threshold, fgHallColor.r, fgHallColor.g, fgHallColor.b, fgHallColor.a);
                }
            }
        }
    }

    if (pRooms)
    {
        for (const std::shared_ptr<Room>& room : *pRooms)
        {
            Array<Vec2> vertices = room->GetVertices();

            S2D_Color color = fgColor;
            S2D_Color lineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

            if (room->eRoomType == Room::MAIN)
            {
                color = hgColor;
                lineColor = { 0.95f, 0.95f, 0.95f, 1.0f };
            }
            else if (room->eRoomType == Room::HALLWAY)
            {
                color = hgHallColor;
                lineColor = { 0.95f, 0.95f, 0.95f, 1.0f };
            }
            else if (bFinished && room->eRoomType == Room::NORMAL)
            {
                continue;
            }

            S2D_DrawQuad(
                vertices[0].x + halfWidth, vertices[0].y + halfHeight, color.r, color.g, color.b, color.a,
                vertices[1].x + halfWidth, vertices[1].y + halfHeight, color.r, color.g, color.b, color.a,
                vertices[2].x + halfWidth, vertices[2].y + halfHeight, color.r, color.g, color.b, color.a,
                vertices[3].x + halfWidth, vertices[3].y + halfHeight, color.r, color.g, color.b, color.a);

            S2D_DrawLine(
                vertices[0].x + halfWidth, vertices[0].y + halfHeight, vertices[1].x + halfWidth, vertices[1].y + halfHeight, 2.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            S2D_DrawLine(
                vertices[1].x + halfWidth, vertices[1].y + halfHeight, vertices[2].x + halfWidth, vertices[2].y + halfHeight, 2.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            S2D_DrawLine(
                vertices[2].x + halfWidth, vertices[2].y + halfHeight, vertices[3].x + halfWidth, vertices[3].y + halfHeight, 2.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            S2D_DrawLine(
                vertices[3].x + halfWidth, vertices[3].y + halfHeight, vertices[0].x + halfWidth, vertices[0].y + halfHeight, 2.0f,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a,
                lineColor.r, lineColor.g, lineColor.b, lineColor.a);
        }
    }

    // Need to do this after because render order
    if (!bFinished)
    {
        if (pTriangles && pSelectedEdges && pSelectedEdges->Size() == 0)
        {
            const S2D_Color green = { 0.0f, 1.0f, 0.0f, 1.0f };

            for (const std::shared_ptr<Triangle>& triangle : *pTriangles)
            {
                // This draws lines multiple times but ehh
                for (Edge edge : triangle->GetEdges())
                {
                    S2D_DrawLine(
                        edge.key->x + halfWidth, edge.key->y + halfHeight, edge.value->x + halfWidth, edge.value->y + halfHeight, 2,
                        green.r, green.g, green.b, green.a,
                        green.r, green.g, green.b, green.a,
                        green.r, green.g, green.b, green.a,
                        green.r, green.g, green.b, green.a);
                }
            }
        }
        else
        {
            const S2D_Color green = { 0.0f, 1.0f, 0.0f, 1.0f };
            for (const Edge& edge : *pSelectedEdges)
            {
                S2D_DrawLine(
                    edge.key->x + halfWidth, edge.key->y + halfHeight, edge.value->x + halfWidth, edge.value->y + halfHeight, 2,
                    green.r, green.g, green.b, green.a,
                    green.r, green.g, green.b, green.a,
                    green.r, green.g, green.b, green.a,
                    green.r, green.g, green.b, green.a);
            }
        }
    }
}

void Renderer::OnKey(S2D_Event e)
{
    switch (e.type)
    {
        case S2D_KEY_DOWN:
            if (strcmp(e.key, "Right") == 0)
                bRunStep = true;
            break;
    }
}
