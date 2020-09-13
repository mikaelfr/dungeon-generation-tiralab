#pragma once

#include <string.h>
#include <iostream>
#include "../util/Memory.h"

template <typename T>
class Array
{
public:
    Array();
    Array(int initialSize);
    Array(const Array<T>& other);
    Array(Array<T>&& other);
    ~Array();

    Array<T>& operator=(const Array<T>& other);
    Array<T>& operator=(Array<T>&& other);

    void Add(T value);
    int Size();

    typedef int (*ComparisonFunction)(const T&, const T&);

    // comparisonFunction should return >0 if right is higher than left
    void Sort(ComparisonFunction func);

    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() { return &data[0]; }
    const_iterator begin() const { return &data[0]; }
    iterator end() { return &data[numElements]; }
    const_iterator end() const { return &data[numElements]; }

    T operator[](int i) const { return data[i]; }
    T& operator[](int i) { return data[i]; }

private:
    const int initialSize = 8;
    int numElements = 0;
    int dataLength = 0;
    T* data = NULL;

    // Assumes that all of the elements in data will fit in the resized array
    void Resize(int newSize);

    T* MergeSort(T* data, int length, ComparisonFunction func);
    T* Merge(T* left, int leftLen, T* right, int rightLen, ComparisonFunction func);
};

// Template function definitions

template <typename T>
Array<T>::Array()
{
    data = new T[initialSize];
    dataLength = initialSize;
}

template <typename T>
Array<T>::Array(int initialSize)
{
    data = new T[initialSize];
    dataLength = initialSize;
}

template <typename T>
Array<T>::Array(const Array<T>& other)
    : data(new T[other.dataLength])
    , dataLength(other.dataLength)
{
    Memory::MemCpy(data, dataLength * sizeof(T), other.data, other.dataLength * sizeof(T));
}

template <typename T>
Array<T>::Array(Array<T>&& other)
    : data(NULL)
    , dataLength(0)
{
    data = other.data;
    dataLength = other.dataLength;
    other.data = NULL;
    other.dataLength = 0;
}

template <typename T>
Array<T>::~Array()
{
    delete[] data;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    if (this != &other)
    {
        delete[] data;

        data = new T[other.dataLength];
        dataLength = other.dataLength;
        Memory::MemCpy(data, dataLength * sizeof(T), other.data, other.dataLength * sizeof(T));
    }

    return *this;
}

template <typename T>
inline Array<T>& Array<T>::operator=(Array<T>&& other)
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        dataLength = other.dataLength;
        other.data = NULL;
        other.dataLength = 0;
    }

    return *this;
}

template <typename T>
void Array<T>::Add(T value)
{
    if (dataLength <= numElements)
    {
        Resize(dataLength * 2);
    }

    data[numElements++] = value;
}

template <typename T>
int Array<T>::Size()
{
    return numElements;
}

template <typename T>
void Array<T>::Sort(ComparisonFunction func)
{
    T* sortedArray = MergeSort(data, numElements, func);

    // If the length of the array is <= 1, the array is sorted by definition
    if (sortedArray != data)
        delete[] data;

    data = sortedArray;
}

template <typename T>
void Array<T>::Resize(int newSize)
{
    if (numElements >= newSize)
    {
        std::cerr << "There are currently more elements than there is room in the new array." << std::endl;
        return;
    }

    T* newArray = new T[newSize];

    if (!Memory::MemCpy(newArray, newSize * sizeof(T), data, numElements * sizeof(T)))
    {
        std::cerr << "Couldn't copy to new array when resizing." << std::endl;
        return;
    }

    delete[] data;
    data = newArray;
}

template <typename T>
T* Array<T>::MergeSort(T* data, int length, ComparisonFunction func)
{
    if (length <= 1)
        return data;

    int halfPoint = length / 2;
    T* left = new T[halfPoint];
    T* right = new T[length - halfPoint];

    if (!Memory::MemCpy(left, halfPoint * sizeof(T), data, halfPoint * sizeof(T)))
    {
        std::cerr << "Couldn't copy left array" << std::endl;
        return NULL;
    }

    if (!Memory::MemCpy(right, (length - halfPoint) * sizeof(T), data + halfPoint, (length - halfPoint) * sizeof(T)))
    {
        std::cerr << "Couldn't copy right array" << std::endl;
        return NULL;
    }

    // Recursively sort both sides
    T* mergedLeft = MergeSort(left, halfPoint, func);
    T* mergedRight = MergeSort(right, length - halfPoint, func);

    // Merge both sorted sides
    T* merged = Merge(mergedLeft, halfPoint, mergedRight, length - halfPoint, func);
    delete[] left;
    delete[] right;

    if (halfPoint > 1)
        delete[] mergedLeft;

    if (length - halfPoint > 1)
        delete[] mergedRight;

    return merged;
}

template <typename T>
T* Array<T>::Merge(T* left, int leftLen, T* right, int rightLen, ComparisonFunction func)
{
    int li = 0, ri = 0, resi = 0;
    T* result = new T[leftLen + rightLen];

    // Build result array by placing smallest of the two sorted arrays
    while (li < leftLen && ri < rightLen)
    {
        if (func(left[li], right[ri]) >= 0)
        {
            result[resi++] = left[li++];
        }
        else
        {
            result[resi++] = right[ri++];
        }
    }

    // Insert the rest into result array
    if (!Memory::MemCpy(result + resi, (leftLen + rightLen - resi) * sizeof(T), left + li, (leftLen - li) * sizeof(T)))
    {
        std::cerr << "Couldn't copy left array" << std::endl;
        return nullptr;
    }

    if (!Memory::MemCpy(result + resi, (leftLen + rightLen - resi) * sizeof(T), right + ri, (rightLen - ri) * sizeof(T)))
    {
        std::cerr << "Couldn't copy right array" << std::endl;
        return nullptr;
    }

    return result;
}
