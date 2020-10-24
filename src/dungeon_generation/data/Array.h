#pragma once

#include <memory>
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

    // Returns inserted value
    T& Add(T value);
    template <typename... Args>
    void Add(T v, Args... values);
    // Removes max one element per call
    // Requires operator == to exist for T
    void Remove(T v);
    int Size() const;

    typedef int (*ComparisonFunction)(const T&, const T&);

    // comparisonFunction should return >0 if right is higher than left
    void Sort(ComparisonFunction func);

    typedef T* iterator;
    typedef const T* const_iterator;

    /*
    Returns an iterator to the first element of the array.
    Used in for each loops.

    @return Iterator to the first element of the array
    */
    iterator begin() { return &data[0]; }

    /*
    Returns a const iterator to the first element of the array.
    Used in for each loops.

    @return Iterator to the first element of the array
    */
    const_iterator begin() const { return &data[0]; }

    /*
    Returns an iterator to just past the last element of the array.
    Used in for each loops.

    @return Iterator to just past the last element of the array
    */
    iterator end() { return &data[numElements]; }

    /*
    Returns a const iterator to just past the last element of the array.
    Used in for each loops.

    @return Iterator to just past the last element of the array
    */
    const_iterator end() const { return &data[numElements]; }

    /*
    Overloaded array index operator for Array
    Returns the value at i.

    @param i Index of the array
    @return Value at i
    */
    T operator[](int i) const { return data[i]; }

    /*
    Overloaded array index operator for Array
    Returns a reference to the value at i.

    @param i Index of the array
    @return Reference to the value at i
    */
    T& operator[](int i) { return data[i]; }

    /*
    Returns the last element of the array by value.

    @return Last element by value
    */
    T Last() const { return data[numElements - 1]; }

    /*
    Returns the last element of the array by reference.

    @return Last element by reference
    */
    T& Last() { return data[numElements - 1]; }

    // Using the stream operator requires T to also have the stream operator defined
    template <typename T1>
    friend std::ostream& operator<<(std::ostream& os, const Array<T1>& arr);

    // Using the stream operator requires T to also have the stream operator defined
    // Thanks, I hate it
    template <typename T2>
    friend std::ostream& operator<<(std::ostream& os, const Array<std::shared_ptr<T2>>& arr);

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

/*
Default constructor for the array
Allocates 8 slots by default
*/
template <typename T>
Array<T>::Array()
{
    data = new T[initialSize];
    dataLength = initialSize;
}

/*
Constructor for the array allowing specifying the initially allocated slots

@param initialSize The number of slots allocated initially
*/
template <typename T>
Array<T>::Array(int initialSize)
{
    data = new T[initialSize];
    dataLength = initialSize;
}

/*
Overloaded copy constructor
Copies data from another Array class with the same type T

@param other Const reference to another array with same type T
*/
template <typename T>
Array<T>::Array(const Array<T>& other)
    : data(new T[other.dataLength])
    , dataLength(other.dataLength)
{
    numElements = other.numElements;
    std::copy(other.begin(), other.end(), data);
}

/*
Overloaded move constructor
Moves data from another Array class with the same type T

@param other An rvalue reference to another array with the same type T
*/
template <typename T>
Array<T>::Array(Array<T>&& other)
    : dataLength(0)
    , data(NULL)
{
    data = other.data;
    dataLength = other.dataLength;
    numElements = other.numElements;
    other.data = NULL;
    other.dataLength = 0;
    other.numElements = 0;
}

/*
Destructor for Array, deletes the data contained in the array
*/
template <typename T>
Array<T>::~Array()
{
    delete[] data;
}

/*
Overloaded copy assignment operator for Array
Copies data from another array and returns a reference to this.

@param other A const reference to another array with the same type T
@return A reference to this
*/
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
        numElements = other.numElements;
        std::copy(other.begin(), other.end(), data);
    }

    return *this;
}

/*
Overloaded move assignment operator for Array
Moves data from another array and returns a reference to this.

@param other An rvalue reference to another array with the same type T
@return A reference to this
*/
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
        numElements = other.numElements;
        other.data = NULL;
        other.dataLength = 0;
        other.numElements = 0;
    }

    return *this;
}

/*
Add a value to this array. Extends the array if required.

@param value A value to be added of type T
@return A reference to the added value in this array
*/
template <typename T>
T& Array<T>::Add(T value)
{
    if (bLocked)
        throw "This array is currently locked. Add not in use.";

    if (dataLength <= numElements)
    {
        Resize(dataLength * 2);
    }

    data[numElements++] = value;
    return data[numElements - 1];
}

/*
A wrapper for adding multiple items at the same time.
Calls Add(T value) for each item.

@param v First value to add
@param values Rest of the values to add, have to be of type T
*/
template <typename T>
template <typename... Args>
inline void Array<T>::Add(T v, Args... values)
{
    Add(v);
    (Add(values), ...);
}

/*
Removes the first value that equals v.
Requires T to have the equality operator defined.

@param v The value to remove
*/
template <typename T>
inline void Array<T>::Remove(T v)
{
    if (bLocked)
        throw "This array is currently locked. Remove not in use.";

    for (int i = 0; i < Size(); i++)
    {
        if (data[i] == v)
        {
            std::move(begin() + i + 1, end(), data + i);
            numElements--;
            return;
        }
    }
}

/*
Returns the number of elements in the array

@return Number of elements in the array
*/
template <typename T>
int Array<T>::Size() const
{
    return numElements;
}

/*
Sorts the array using merge sort and the provided comparison function.
ComparisonFunction should return >0 if right is higher than left.

@param func A pointer to a comparison function
*/
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

/*
Overloaded stream operator for Array
Outputs the array into an ostream in json format.
Requires T1 to have the stream operator defined.

@param os Reference to an ostream where the array will be outputted
@param arr Const reference to outputted array
@return Output stream os with arr outputted
*/
template <typename T1>
std::ostream& operator<<(std::ostream& os, const Array<T1>& arr)
{
    os << '[';

    for (int i = 0; i < arr.Size(); i++)
    {
        os << arr[i];
        if (i != arr.Size() - 1)
            os << ", ";
    }

    os << ']';
    return os;
}

/*
Overloaded stream operator for Array
Outputs the array into an ostream in json format.
Requires T2 to have the stream operator defined.
Specifically designed to output the objects inside shared pointers instead
of the shared pointers themselves.
Only called for arrays that contain shared pointers.

@param os Reference to an ostream where the array will be outputted
@param arr Const reference to outputted array
@return Output stream os with arr outputted
*/
template <typename T2>
std::ostream& operator<<(std::ostream& os, const Array<std::shared_ptr<T2>>& arr)
{
    os << '[';

    for (int i = 0; i < arr.Size(); i++)
    {
        os << *arr[i];
        if (i != arr.Size() - 1)
            os << ", ";
    }

    os << ']';
    return os;
}

/*
Locks the array, prohibiting all operations that would modify memory.
Not currently used since I opted to use shared pointers instead.
*/
template <typename T>
inline void Array<T>::Lock()
{
    bLocked = true;
}

/*
Unlocks the array, permitting all operations that would modify memory.
Not currently used since I opted to use shared pointers instead.
*/
template <typename T>
inline void Array<T>::Unlock()
{
    bLocked = false;
}

/*
Resize the array to newSize.
Expects newSize to be able to hold all elements currently in the array.

@param newSize New size the array will be resized to
*/
template <typename T>
void Array<T>::Resize(int newSize)
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

/*
Merge sort O(n log n)

@param data Pointer to an array that will be sorted
@param length Length of the array
@param func Comparison function that will be called when comparing elements
@return Pointer to the sorted array
*/
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

/*
Merges two sorted arrays together using a comparison function

@param left Pointer to the left array
@param leftLen Length of the left array
@param right Pointer to the right array
@param rightLen Length of the right array
@param func Comparison function that will be called when comparing elements
@return Pointer to an array with left and right array combined and sorted in it
*/
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
