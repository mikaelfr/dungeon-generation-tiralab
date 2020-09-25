#pragma once

#include "Array.h"

// There won't be more than a few elements in each set
// so for our usecase, it's fine to just iterate through the array
// for every new addition
template <typename T>
class Set : public Array<T>
{
public:
    T& Add(T value);
    template <typename... Args>
    void Add(T v, Args... values);
};

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

template <typename T>
template <typename... Args>
inline void Set<T>::Add(T v, Args... values)
{
    Add(v);
    (Add(values), ...);
}
