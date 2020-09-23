#include "Triangle.h"
#include "Triangle.h"
#include "Triangle.h"
#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(std::shared_ptr<Room> a, std::shared_ptr<Room> b, std::shared_ptr<Room> c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

// Point not inside circumcirle
bool Triangle::IsDelaunay(Vec2 point)
{
    if (Math::IsClockwise(*a, *b, *c))
    {
        return Math::Determinant(*c, *b, *a, point) <= 0;
    }
    else
    {
        return Math::Determinant(*a, *b, *c, point) <= 0;
    }
}

bool Triangle::HasVertFromSuperTriangle()
{
    // Super triangle vertices (rooms) have the height and width set to -1
    for (std::shared_ptr<Room> r : GetVerts())
    {
        if (r->width == -1 && r->height == -1)
            return true;
    }

    return false;
}

Triangle::Edge Triangle::GetClosestVerts(const Vec2& point)
{
    float aLen = (*a - point).Length();
    float bLen = (*b - point).Length();
    float cLen = (*c - point).Length();

    char largest = (aLen > bLen) ? ((aLen > cLen) ? 0 : 2) : ((bLen > cLen) ? 1 : 2);

    switch (largest)
    {
        case 0:
            return Tuple(b, c);
        case 1:
            return Tuple(a, c);
        case 2:
            return Tuple(a, b);
    }

    return Tuple(a, b);
}

bool Triangle::HasEdge(const Edge& edge)
{
    for (Edge e : GetEdges())
    {
        // Probably fine to compare shared pointers, since we shouldnt have multiple copies of the same room
        if (e.key == edge.key && e.value == edge.value)
            return true;

        if (e.key == edge.value && e.value == edge.key)
            return true;
    }

    return false;
}

Verts Triangle::GetVerts()
{
    return Verts(this);
}

Edges Triangle::GetEdges()
{
    return Edges(this);
}

// Definitions for Verts and Edges
Verts::Verts(Triangle* pTriangle)
{
    this->pTriangle = pTriangle;
}

typedef ClassIterator<std::shared_ptr<Room>, Verts> iterator;

Verts::iterator::GetElementFunction Verts::lambda = [](int it, Verts* pThis) {
    switch (it)
    {
        case 0:
            return pThis->pTriangle->a;
        case 1:
            return pThis->pTriangle->b;
        case 2:
            return pThis->pTriangle->c;
    }

    throw "Iterator out of range";
};

Verts::iterator Verts::begin()
{
    return iterator(0, this, lambda);
}

Verts::iterator Verts::end()
{
    return iterator(3, this, lambda);
}

// Definitions for Edges
Edges::Edges(Triangle* pTriangle)
{
    this->pTriangle = pTriangle;
}

Edges::iterator::GetElementFunction Edges::lambda = [](int it, Edges* pThis) {
    switch (it)
    {
        case 0:
            return Triangle::Edge(pThis->pTriangle->a, pThis->pTriangle->b);
        case 1:
            return Triangle::Edge(pThis->pTriangle->b, pThis->pTriangle->c);
        case 2:
            return Triangle::Edge(pThis->pTriangle->c, pThis->pTriangle->a);
    }

    throw "Iterator out of range";
};

Edges::iterator Edges::begin()
{
    return iterator(0, this, lambda);
}

Edges::iterator Edges::end()
{
    return iterator(3, this, lambda);
}
