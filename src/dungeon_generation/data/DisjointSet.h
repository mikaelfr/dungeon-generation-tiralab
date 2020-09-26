#pragma once

template <typename T>
class DisjointSet
{
public:
    DisjointSet(T value);

    DisjointSet<T>& Find(DisjointSet<T>* x);

    // Union
    DisjointSet<T>& operator+=(const DisjointSet<T>& other);

private:
    DisjointSet<T>* pParent = nullptr;
    T value;
};

template <typename T>
inline DisjointSet<T>::DisjointSet(T value)
{
    this->value = value;
    // root
    this->pParent = this;
}

template <typename T>
inline DisjointSet<T>& DisjointSet<T>::Find(DisjointSet<T>* x)
{
    while (x->pParent != x)
    {
        x = x->pParent;
    }
    return x;
}

template <typename T>
inline DisjointSet<T>& DisjointSet<T>::operator+=(const DisjointSet<T>& other)
{
    DisjointSet<T>& x = Find(this);
    DisjointSet<T>& y = Find(&other);

    if (x == y)
        return *this;

    y->pParent = this;
    return *this;
}
