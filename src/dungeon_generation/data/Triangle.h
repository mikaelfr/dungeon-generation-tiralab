#pragma once

#include <memory>
#include "Room.h"
#include "../util/Math.h"
#include "Tuple.h"
#include "ClassIterator.h"

// Forward def for Verts and Edges
class Triangle;

/*
Struct for edges

Only practical difference between this struct and a typedef is that
this struct has a equals operator overload for checking if the edges are the same
while ignoring the direction
*/
struct Edge : public Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>
{
    /*
    Default constructor
    Calls tuple default constructor
    */
    Edge()
        : Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>()
    {
    }

    /*
    Constructor that creates an edge from pointers to rooms a and b
    Calls tuple constructor with a and b

    @param a Pointer to room a
    @param b Pointer to room b
    */
    Edge(std::shared_ptr<Room> a, std::shared_ptr<Room> b)
        : Tuple<std::shared_ptr<Room>, std::shared_ptr<Room>>(a, b)
    {
    }

    /*
    Overloaded equality operator
    Ignores direction

    @param other Edge to compare this to
    @return True if both edges have same points
    */
    inline bool operator==(const Edge& other) const
    {
        return (this->key == other.key && this->value == other.value) ||
               (this->key == other.value && this->value == other.key);
    }
};

/*
Empty support class for iterating over the vertices of a triangle automagically
*/
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

/*
Empty support class for iterating over the edges of a triangles automagically
*/
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

/*
Class for triangle data type, contains many helper functions
*/
class Triangle
{
public:
    Triangle();
    Triangle(std::shared_ptr<Room> a, std::shared_ptr<Room> b, std::shared_ptr<Room> c);

    // Point not inside circumcirle
    bool IsDelaunay(Vec2 point);

    bool HasVertFromSuperTriangle();

    bool HasEdge(const Edge& edge);

    Verts GetVerts();
    Edges GetEdges();

    std::shared_ptr<Room> a;
    std::shared_ptr<Room> b;
    std::shared_ptr<Room> c;
};
