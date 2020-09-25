#pragma once

#include <memory>
#include "Room.h"
#include "../util/Math.h"
#include "Tuple.h"
#include "ClassIterator.h"

// Forward def for Verts and Edges
class Triangle;

struct Edge : public Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>
{
    Edge()
        : Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>() {}

    Edge(std::shared_ptr<Room> a, std::shared_ptr<Room> b)
        : Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>(a, b) {}

    // Undirected
    inline bool operator==(const Edge& other) const
    {
        return (this->key == other.key && this->value == other.value) ||
                (this->key == other.value && this->value == other.key);
    }
};

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

    typedef ClassIterator<Edge, Edges> iterator;

    // Marking as static so we can define it in cpp file
    static iterator::GetElementFunction lambda;

    iterator begin();
    iterator end();

    Triangle* pTriangle = NULL;
};

class Triangle
{
public:
    Triangle();
    Triangle(std::shared_ptr<Room> a, std::shared_ptr<Room> b, std::shared_ptr<Room> c);

    // Point not inside circumcirle
    bool IsDelaunay(Vec2 point);

    bool HasVertFromSuperTriangle();

    Edge GetClosestVerts(const Vec2& point);

    bool HasEdge(const Edge& edge);

    Verts GetVerts();
    Edges GetEdges();

    std::shared_ptr<Room> a;
    std::shared_ptr<Room> b;
    std::shared_ptr<Room> c;
};
