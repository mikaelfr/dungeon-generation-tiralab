#pragma once

#include <string>
#include "Array.h"
#include "../util/Math.h"

template <typename T>
class BinaryHeap
{
public:
    BinaryHeap();
    BinaryHeap(int initialSize);
    ~BinaryHeap();

    void Push(T value);
    T Pop();

    int Size() const;

    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() { return &data[0]; }
    const_iterator begin() const { return &data[0]; }
    iterator end() { return &data[numElements]; }
    const_iterator end() const { return &data[numElements]; }

private:
    const int initialSize = 8;
    int numElements = 0;
    int dataLength = 0;
    T* data = NULL;

    void Resize(int newSize);
    void MinHeapify(int index);
    void MinHeapifyUp(int index);
};

template <typename T>
inline BinaryHeap<T>::BinaryHeap()
{
    data = new T[initialSize];
    dataLength = initialSize;
}

template <typename T>
inline BinaryHeap<T>::BinaryHeap(int initialSize)
{
    data = new T[initialSize];
    dataLength = initialSize;
}

template <typename T>
inline BinaryHeap<T>::~BinaryHeap()
{
    delete[] data;
}

template <typename T>
inline void BinaryHeap<T>::Push(T value)
{
    if (dataLength <= numElements)
    {
        Resize(dataLength * 2 + 2);
    }

    data[numElements++] = value;
    MinHeapifyUp(numElements - 1);
}

template <typename T>
inline T BinaryHeap<T>::Pop()
{
    if (Size() <= 0)
        throw "Cannot pop from empty array.";

    T temp = data[0];

    if (Size() == 1)
    {
        numElements--;
        return temp;
    }

    data[0] = data[numElements--];
    MinHeapify(0);
    return temp;
}

template <typename T>
inline int BinaryHeap<T>::Size() const
{
    return numElements;
}

template <typename T>
inline void BinaryHeap<T>::Resize(int newSize)
{
    if (numElements >= newSize)
    {
        throw "There are currently more elements than there is room in the new array.";
    }

    T* newArray = new T[newSize];

    std::copy(begin(), end(), newArray);

    delete[] data;
    dataLength = newSize;
    data = newArray;
}

template <typename T>
inline void BinaryHeap<T>::MinHeapify(int index)
{
    int i = index;
    bool bInOrder = false;

    while (!bInOrder)
    {
        int leftIdx = 2 * i + 1;
        int rightIdx = 2 * i + 2;
        int smallestIdx = i;

        if (leftIdx <= numElements && data[leftIdx] < data[smallestIdx])
        {
            smallestIdx = leftIdx;
        }

        if (rightIdx <= numElements && data[rightIdx] < data[smallestIdx])
        {
            smallestIdx = rightIdx;
        }

        if (smallestIdx != i)
        {
            T temp = data[smallestIdx];
            data[smallestIdx] = data[i];
            data[i] = temp;
            i = smallestIdx;
        }
        else
        {
            bInOrder = true;
        }
    }
}

template <typename T>
inline void BinaryHeap<T>::MinHeapifyUp(int index)
{
    int i = index;
    bool bInOrder = false;

    while (!bInOrder)
    {
        int parentIdx = (int)(i / 2);
        int smallestIdx = i;

        if (data[parentIdx] < data[smallestIdx])
        {
            smallestIdx = leftIdx;
        }

        if (smallestIdx != i)
        {
            T temp = data[smallestIdx];
            data[smallestIdx] = data[i];
            data[i] = temp;
            i = smallestIdx;
        }
        else
        {
            bInOrder = true;
        }
    }
}
