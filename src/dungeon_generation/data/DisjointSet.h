#pragma once

template <typename T>
class DisjointSet
{
public:
    DisjointSet();
    DisjointSet(T value);

    DisjointSet<T>* Find();

    bool operator==(const DisjointSet<T>& other);
    bool operator!=(const DisjointSet<T>& other);

    // Union
    DisjointSet<T>& operator+=(DisjointSet<T>& other);

private:
    // NULL means root
    DisjointSet<T>* pParent;
    T value;
};

/*
Default constructor for the disjoint set
*/
template <typename T>
inline DisjointSet<T>::DisjointSet()
{
}

/*
Constructor for the disjoint set for setting the value of this node

@param value Value of this node
*/
template <typename T>
inline DisjointSet<T>::DisjointSet(T value)
{
    this->value = value;
    // root
    this->pParent = NULL;
}

/*
Finds the root of the tree this node is a part of and returns a pointer to it

@return A pointer to the root disjoint set
*/
template <typename T>
inline DisjointSet<T>* DisjointSet<T>::Find()
{
    DisjointSet<T>* x = this;
    while (x->pParent)
    {
        x = x->pParent;
    }
    return x;
}

/*
Overload for the equality operator.
Checks if the value and parent are the same.
Requires type T to have the equality operator defined.

@param other The disjoint set to compare this to
@return True if this equals other
*/
template <typename T>
inline bool DisjointSet<T>::operator==(const DisjointSet<T>& other)
{
    return this->value == other.value && this->pParent == other.pParent;
}

/*
Overload of the inequality operator.
Negates the result of the equality operator.

@param other The disjoint set to compare this to
@return True if this doesn't equal other
*/
template <typename T>
inline bool DisjointSet<T>::operator!=(const DisjointSet<T>& other)
{
    return !operator==(other);
}

/*
Overload for the addition assignment operator.
Implements the union operation for disjoint sets.

@param other Other disjoint set to make an union with
@return A reference to this
*/
template <typename T>
inline DisjointSet<T>& DisjointSet<T>::operator+=(DisjointSet<T>& other)
{
    DisjointSet<T>* x = Find();
    DisjointSet<T>* y = other.Find();

    if (x == y)
        return *this;

    y->pParent = this;
    return *this;
}
