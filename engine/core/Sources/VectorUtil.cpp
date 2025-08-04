//
// Created by User on 04.08.2025.
//

#include "../Header/VectorUtil.h"

#include <ostream>
#include <valarray>

namespace Engine {
    //VECTOR3

    // Constructors
    vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Vector addition
    vec3 vec3::operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    vec3 vec3::operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    vec3 vec3::operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product
    float vec3::dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    vec3 vec3::cross(const vec3& other) const {
        return vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Vector length
    float vec3::length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    // Normalized vector
    vec3 vec3::normalized() const {
        float len = length();
        if (len > 0) {
            return vec3(x/len, y/len, z/len);
        }
        return *this;
    }

    // Output (for debugging)
    std::ostream& operator<<(std::ostream& os, const vec3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    // VECTOR2
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
