//
// Created by augus on 06.03.2026.
//

#ifndef INC_3DENGINE_VECTOR_H
#define INC_3DENGINE_VECTOR_H
#pragma once
#include <algorithm>
#include <cstddef>
#include <iosfwd>
#include <ostream>
#include <type_traits>

#endif //INC_3DENGINE_VECTOR_H

// lets you create a vector of any type T and dimension D
template<typename T, std::size_t D>
struct vec {
    // T data[D];
    // thanks to deepseek for union trick
    union
    {
        T data[D];

        struct { T x, y, z, w; };
    };

    // standart constructor v() = {0,0,0}
    constexpr vec() {
        std::fill(data, data + D, T{}); // T{} returns standard value. for int 0, for boolean false, etc.
    }
    // args constructor v(1,2,3) = {1,2,3}
    // danke an deepseek für den conflict fix der constructoren
    template<typename... Args,
         typename = std::enable_if_t<(sizeof...(Args) != 1)>>
    constexpr vec(Args... args): data{static_cast<T>(args)...} {
        static_assert(sizeof...(Args) == D, "Incompatible arguments for vec!");
    }
    // fill constructor v(3) = {3,3,3}
    constexpr vec(T fillNumber) {
        std::fill(data, data + D, fillNumber);
    }

    constexpr T& operator[](std::size_t i) { return data[i]; }
    constexpr const T& operator[](std::size_t i) const { return data[i]; }

    // standart vec-vec operations
    constexpr vec operator+(const vec& other) const {
        vec<T,D> result;
        for (size_t i = 0; i < D; i++) {
            result[i] = data[i] + other.data[i];
        }
        return result;
    }
    constexpr vec operator-(const vec& other) const {
        vec<T,D> result;
        for (size_t i = 0; i < D; i++) {
            result[i] = data[i] - other.data[i];
        }
        return result;
    }
    constexpr void operator+=(const vec& other) {
        for (size_t i = 0; i < D; i++) {
            data[i] += other.data[i];
        }
    }
    constexpr void operator-=(const vec& other) {
        for (size_t i = 0; i < D; i++) {
            data[i] -= other.data[i];
        }
    }

    // standart vec-scalar operations
    constexpr vec operator*(T scalar) const {
        vec<T,D> result;
        for (size_t i = 0; i < D; i++) {
            result[i] = data[i] * scalar;
        }
        return result;
    }
    constexpr void operator*=(T scalar) {
        for (size_t i = 0; i < D; i++) {
            data[i] *= scalar;
        }
    }
    constexpr vec operator/(T scalar) const {
        vec<T,D> result;
        for (size_t i = 0; i < D; i++) {
            result[i] = data[i] / scalar;
        }
        return result;
    }
    constexpr void operator/=(T scalar) {
        for (size_t i = 0; i < D; i++) {
            data[i] /= scalar;
        }
    }

    // dot, length, normalize
    constexpr T dot(const vec& other) const {
        T result = T{};
        for (size_t i = 0; i < D; i++) {
            result += data[i] * other.data[i];
        }
        return result;
    }
    T length() const {
        return sqrt(dot(*this));
    }
    T lengthSquared() const { // better performance because no sqrt
        return dot(*this);
    }

    constexpr vec normalized() const {
        T len = length();
        vec<T,D> result;
        if (len > 0) {
            return *this / len;
        }
        return *this;
    }
    constexpr void normalize() {
        float len = length();
        if (len > 0) {
            *this /= len;
        }
    }

    // static distance
    static constexpr T distance(const vec& a, const vec& b){
        return (a - b).length();
    }
    static constexpr T distanceSquared(const vec& a, const vec& b) {
        return (a - b).lengthSquared();
    }

    // hadamard operation
    constexpr vec mul(const vec &other) const{
        vec result;
        for (size_t i = 0; i < D; i++) {
            result[i] = data[i] * other.data[i];
        }
        return result;
    }
    constexpr vec div(const vec &other) const {
        vec result;
        for (size_t i = 0; i < D; i++) {
            result[i] = data[i] / other.data[i];
        }
        return result;
    }

    // 3D specific methdos
    constexpr vec cross(const vec& other) const {
        static_assert(D == 3, "Cross-Product in this implementation is only applicable to 3-Dimensional Vectors");
        return vec(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        );
    }


    constexpr vec operator-() const {
        vec result;
        for (size_t i = 0; i < D; i++)
            result.data[i] = -data[i];
        return result;
    }

    constexpr bool operator==(const vec& other) const {
        for (size_t i = 0; i < D; i++)
            if (data[i] != other.data[i])
                return false;
        return true;
    }

    constexpr size_t size() const {return D;}

    // Getter for legacy code
    constexpr T getX() const{static_assert(D > 0, "This Vector has no X component"); return x;}
    constexpr T getY() const{static_assert(D > 1, "This Vector has no Y component"); return y;}
    constexpr T getZ() const{static_assert(D > 2, "This Vector has no Z component"); return z;}
    constexpr T getW() const{static_assert(D > 3, "This Vector has no W component"); return w;}
};
// typedefs
using vec2 = vec<float,2>;
using vec3 = vec<float,3>;
using vec4 = vec<float,4>;

using ivec2 = vec<int,2>;


// für debug prints
template<typename T, std::size_t D>
std::ostream& operator<<(std::ostream& os, const vec<T,D>& v)
{
    os << "(";
    for (std::size_t i = 0; i < D; i++)
    {
        os << v[i];
        if (i < D - 1)
            os << ", ";
    }
    os << ')';
    return os;
}
// um auch scalar * vec und nicht nur vec * scalar zu erlauben
template<typename T, std::size_t D>
constexpr vec<T,D> operator*(T scalar, const vec<T,D>& v)
{
    return v * scalar;
}