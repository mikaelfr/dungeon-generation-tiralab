#pragma once

#include <memory>
#include "Room.h"
#include "../util/Math.h"
#include "Tuple.h"
#include "ClassIterator.h"

// Forward def for Verts and Edges
class Triangle;

struct Verts
{
    Verts(Triangle* pTriangle);

    typedef ClassIterator<std::shared_ptr<Room>, Verts> iterator;

    // Marking as static so we can define it in cpp file
    static iterator::GetElementFunction lambda;

    iterator begin();
    iterator end();

    Triangle* pTriangle = NULL;
};

struct Edges
{
    Edges(Triangle* pTriangle);

    typedef ClassIterator<Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>, Edges> iterator;

    // Marking as static so we can define it in cpp file
    static iterator::GetElementFunction lambda;

    iterator begin();
    iterator end();

    Triangle* pTriangle = NULL;
};

class Triangle
{
public:
    typedef Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>> Edge;

    Triangle();
    Triangle(std::shared_ptr<Room> a, std::shared_ptr<Room> b, std::shared_ptr<Room> c);

    // Point not inside circumcirle
    bool IsDelaunay(Vec2 point);

    bool HasVertFromSuperTriangle();

    Edge GetClosestVerts(const Vec2& point);

    bool HasEdge(const Edge edge);

    Verts GetVerts();
    Edges GetEdges();

    std::shared_ptr<Room> a;
    std::shared_ptr<Room> b;
    std::shared_ptr<Room> c;
};
