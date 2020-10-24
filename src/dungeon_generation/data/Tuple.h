#pragma once

#include <iostream>

/*
Generic Tuple implementation
*/
template <typename T, typename U>
struct Tuple
{
    /*
    Default constructor
    T and U will end up with default values
    */
    Tuple() 
    {
        key = T();
        value = U();
    }

    /*
    Constructor for key, value pair

    @param key Key with an arbitrary type
    @param value Value with an arbitrary type
    */
    Tuple(T key, U value)
    {
        this->key = key;
        this->value = value;
    }

    T key;
    U value;

    /*
    Overload for stream operator
    Inserts the string representation of this object into the stream
    Note: T and U should have stream operators defined

    @param os Reference to the stream
    @param tuple Const reference to the streamed tuple
    @return os
    */
    friend std::ostream& operator<<(std::ostream& os, const Tuple<T, U>& tuple)
    {
        // This is currently specially made for nicer json output for lines
        // (so instead of the end result being {"key": ..., "value": ...}
        //  the result ends up being {"start": ..., "end": ...})
        os << '{' << "\"start\": " << tuple.key << ", \"end\": " << tuple.value << '}';
        return os;
    }
};
