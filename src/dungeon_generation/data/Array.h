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

    // Locks the array, permitting no operations that could modify memory
    void Lock();
    void Unlock();

private:
    const int initialSize = 8;
    int numElements = 0;
    int dataLength = 0;
    T* data = NULL;
    bool bLocked = false;

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
    std::copy(other.begin(), other.end(), data);
}

template <typename T>
Array<T>::Array(Array<T>&& other)
    : dataLength(0)
    , data(NULL)
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
        if (bLocked)
            throw "This array is currently locked. Copy assignment operator not in use.";

        delete[] data;

        data = new T[other.dataLength];
        dataLength = other.dataLength;
        std::copy(other.begin(), other.end(), data);
    }

    return *this;
}

template <typename T>
inline Array<T>& Array<T>::operator=(Array<T>&& other)
{
    if (this != &other)
    {
        if (bLocked)
            throw "This array is currently locked. Move assignment operator not in use.";

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
    if (bLocked)
        throw "This array is currently locked. Add not in use.";

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
    if (bLocked)
        throw "This array is currently locked. Sort not in use.";

    T* sortedArray = MergeSort(data, numElements, func);

    // If the length of the array is <= 1, the array is sorted by definition
    if (sortedArray != data)
        delete[] data;

    data = sortedArray;
}

template <typename T>
inline void Array<T>::Lock()
{
    bLocked = true;
}

template <typename T>
inline void Array<T>::Unlock()
{
    bLocked = false;
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

    std::copy(begin(), end(), newArray);

    delete[] data;
    dataLength = newSize;
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

    std::copy(data, data + halfPoint, left);
    std::copy(data + halfPoint, data + length, right);

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
    std::copy(left + li, left + leftLen, result + resi);
    std::copy(right + ri, right + rightLen, result + resi);

    return result;
}
