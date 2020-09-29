#pragma once

#include <iostream>

template <typename T, typename U>
struct Tuple
{
    Tuple() {}
    Tuple(T key, U value)
    {
        this->key = key;
        this->value = value;
    }

    T key;
    U value;

    // T and U should have stream operators defined
    friend std::ostream& operator<<(std::ostream& os, const Tuple<T, U>& tuple)
    {
        // This is currently specially made for nicer json output for lines
        os << '{' << "\"start\": " << tuple.key << ", \"end\": " << tuple.value << '}';
        return os;
    }
};
