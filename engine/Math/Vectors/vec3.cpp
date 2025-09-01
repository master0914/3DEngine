//
// Created by Master0914 on 01.09.2025.
//

#include "VectorUtil.h"
#include <ostream>
#include <valarray>
#include <iomanip>


namespace Engine {
    //VECTOR3------------------------------------------------------------------

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
}