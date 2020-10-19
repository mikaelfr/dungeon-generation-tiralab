#include "Triangle.h"

/*
Default constructor
*/
Triangle::Triangle() {}

/*
Constructor for constructing a triangle from pointers to three rooms

@param a Pointer to a room
@param b Pointer to a room
@param c Pointer to a room
*/
Triangle::Triangle(std::shared_ptr<Room> a, std::shared_ptr<Room> b, std::shared_ptr<Room> c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

/*
Calculates quickly using determinants if a given point is inside the circumcircle
constructed from the points of the triangle

@param point Point to check against the triangle
@return True if the point is not inside the circumcircle (i.e. it fulfills the Delaunay condition)
*/
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

/*
Returns true if this triangle has a vertex from the super triangle
Super triangle is defined with "broken" rooms (i.e. they have a width and height of -1)

@return True if this triangle has a vert from the super triangle
*/
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

/*
Returns true if this triangle has edge
Ignores direction

@param edge Const reference to the edge
@return True if this triangle has the specified edge
*/
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

/*
Returns a dummy class that can be used to iterate over the verts (rooms) in this triangle

@return A new Verts object bound to this
*/
Verts Triangle::GetVerts()
{
    return Verts(this);
}

/*
Returns a dummy class that can be used to iterate over the edges (tuple of rooms) in this triangle

@return A new Edges object bound to this
*/
Edges Triangle::GetEdges()
{
    return Edges(this);
}

// Definitions for Verts and Edges
/*
Constructor for Verts

@param pTriangle Pointer to the triangle this object is bound to
*/
Verts::Verts(Triangle* pTriangle)
{
    this->pTriangle = pTriangle;
}

/*
Lambda function defining the returned object for each valid iterator value
Returns the vertices of the triangle in order a, b, c

@param it Current iterator value
@param pThis Pointer to current Verts object (needed since this is static and we cant use a capturing lambda)
@return Shared pointer to room for valid iterator value
*/
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

/*
Returns iterator for first vertex

@return ClassIterator for vertices at value 0
*/
Verts::iterator Verts::begin()
{
    return iterator(0, this, lambda);
}

/*
Returns iterator for 1 past last vertex

@return ClassIterator for vertices at value 3
*/
Verts::iterator Verts::end()
{
    return iterator(3, this, lambda);
}

// Definitions for Edges
/*
Constructor for Edges

@param pTriangle Pointer to the triangle this object is bound to
*/
Edges::Edges(Triangle* pTriangle)
{
    this->pTriangle = pTriangle;
}

/*
Lambda function defining the returned object for each valid iterator value
Returns the edges of the triangle in order (a, b), (b, c), (c, a)

@param it Current iterator value
@param pThis Pointer to current Edges object (needed since this is static and we cant use a capturing lambda)
@return A new Edge object for valid iterator value
*/
Edges::iterator::GetElementFunction Edges::lambda = [](int it, Edges* pThis) {
    switch (it)
    {
        case 0:
            return Edge(pThis->pTriangle->a, pThis->pTriangle->b);
        case 1:
            return Edge(pThis->pTriangle->b, pThis->pTriangle->c);
        case 2:
            return Edge(pThis->pTriangle->c, pThis->pTriangle->a);
    }

    throw "Iterator out of range";
};

/*
Returns iterator for first edge

@return ClassIterator for edges at value 0
*/
Edges::iterator Edges::begin()
{
    return iterator(0, this, lambda);
}

/*
Returns iterator for 1 past last edge

@return ClassIterator for edges at value 3
*/
Edges::iterator Edges::end()
{
    return iterator(3, this, lambda);
}
