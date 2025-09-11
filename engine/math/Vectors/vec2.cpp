//
// Created by Master0914 on 01.09.2025.
//

#include "VectorUtil.h"
#include <ostream>
#include <valarray>
#include <iomanip>


namespace Engine {
    // VECTOR2-------------------------------------------------------------------------

    vec2::vec2() : x(0.0f), y(0.0f) {}

    vec2::vec2(float x, float y) : x(x), y(y) {}

    vec2 vec2::operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 vec2::operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2 vec2::operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    float vec2::dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    float vec2::length() const {
        return std::sqrt(x * x + y * y);
    }

    vec2 vec2::normalized() const {
        float len = length();
        if (len > 0) {
            return vec2(x / len, y / len);
        }
        return vec2();
    }

    std::ostream& operator<<(std::ostream& os, const vec2& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
}