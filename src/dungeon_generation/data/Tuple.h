#pragma once

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
};
