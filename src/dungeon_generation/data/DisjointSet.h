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

template <typename T>
inline DisjointSet<T>::DisjointSet()
{
}

template <typename T>
inline DisjointSet<T>::DisjointSet(T value)
{
    this->value = value;
    // root
    this->pParent = NULL;
}

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

template <typename T>
inline bool DisjointSet<T>::operator==(const DisjointSet<T>& other)
{
    return this->value == other.value && this->pParent == other.pParent;
}

template <typename T>
inline bool DisjointSet<T>::operator!=(const DisjointSet<T>& other)
{
    return !operator==(other);
}

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
