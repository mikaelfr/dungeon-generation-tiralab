#pragma once

// Class for turning a subset of member variables loopable with for each
// T type of iterated item, U is the type of the class
template <typename T, typename U>
class ClassIterator
{
public:
    typedef T (*GetElementFunction)(int, U*);

    ClassIterator(int it, U* pClass, GetElementFunction pGetElementFunc);

    T operator*();
    void operator++();
    bool operator!=(ClassIterator it) const;

private:
    int iterator = 0;

    GetElementFunction pGetElementFunc = 0;
    U* pClass = 0;
};

template <typename T, typename U>
inline ClassIterator<T, U>::ClassIterator(int it, U* pClass, GetElementFunction pGetElementFunc)
{
    this->iterator = it;
    this->pClass = pClass;
    this->pGetElementFunc = pGetElementFunc;
}

template <typename T, typename U>
inline T ClassIterator<T, U>::operator*()
{
    return pGetElementFunc(iterator, pClass);
}

template <typename T, typename U>
inline void ClassIterator<T, U>::operator++()
{
    iterator++;
}

template <typename T, typename U>
inline bool ClassIterator<T, U>::operator!=(ClassIterator it) const
{
    return iterator != it.iterator;
}
