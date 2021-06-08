#pragma once
#include <type_traits>
namespace eng {

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Vector {
    Vector() : x(0), y(0), z(0), w(0) {}
    Vector (T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vector (T x, T y, T z) : x(x), y(y), z(z), w(0) {}
    Vector (T x, T y) : x(x), y(y), z(0), w(0) {}
    Vector (T x) : x(x), y(0), z(0), w(0) {}
    T x;
    T y;
    T z;
    T w;
};
}
