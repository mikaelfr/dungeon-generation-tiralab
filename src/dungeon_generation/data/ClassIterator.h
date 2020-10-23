#pragma once

/*
Class for turning a subset of member variables loopable with for each
T type of iterated item, U is the type of the class
*/
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

/*
Constructor for ClassIterator

@param it Iterator value for this iterator
@param pClass Pointer to the class instance of type U
@param pGetElementFunc Pointer to the function giving values of type T for every valid iterator value
*/
template <typename T, typename U>
inline ClassIterator<T, U>::ClassIterator(int it, U* pClass, GetElementFunction pGetElementFunc)
{
    this->iterator = it;
    this->pClass = pClass;
    this->pGetElementFunc = pGetElementFunc;
}

/*
Overload for the dereferencing operator
Returns the value given by GetElementFunc defined in the constructor for this given iterator value.

@return Value from GetElementFunc
*/
template <typename T, typename U>
inline T ClassIterator<T, U>::operator*()
{
    return pGetElementFunc(iterator, pClass);
}

/*
Overload for the increment operator
Increments the iterator value by 1
*/
template <typename T, typename U>
inline void ClassIterator<T, U>::operator++()
{
    iterator++;
}

/*
Overload for the inequality operator
Checks if the iterator values for this and it are same

@param it Other iterator
@return True if iterator values of this and other it are same
*/
template <typename T, typename U>
inline bool ClassIterator<T, U>::operator!=(ClassIterator it) const
{
    return iterator != it.iterator;
}
