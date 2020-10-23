#pragma once

#include "Array.h"

/*
A simple set data structure that extends the Array class. Guarantees
that there won't be any duplicates in the set. Requires the equality
operator to be defined for type T.

There won't be more than a few elements in each set
so for our usecase, it's fine to just iterate through the array
for every new addition
*/
template <typename T>
class Set : public Array<T>
{
public:
    T& Add(T value);
    template <typename... Args>
    void Add(T v, Args... values);
};

/*
Adds a new element into the array if it doesn't already exist

@param value Value to be added
@return Reference to the added value in the array, or a reference to a pre-existing element if value already exists
*/
template <typename T>
inline T& Set<T>::Add(T value)
{
    for (T& v : *this)
    {
        if (v == value)
            return v;
    }

    return Array<T>::Add(value);
}

/*
Adds multiple new elements into the array, if they don't already exist

@param v First value to be added
@param values Rest of the values to be added
*/
template <typename T>
template <typename... Args>
inline void Set<T>::Add(T v, Args... values)
{
    Add(v);
    (Add(values), ...);
}
