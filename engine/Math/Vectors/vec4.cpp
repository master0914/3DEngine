//
// Created by Master0914 on 01.09.2025.
//

#include "VectorUtil.h"
#include <ostream>
#include <valarray>
#include <iomanip>

namespace Engine {
    vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

    vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    vec4 vec4::operator+(const vec4& other) const {
        return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    vec4 vec4::operator-(const vec4& other) const {
        return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    vec4 vec4::operator*(float scalar) const {
        return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    float vec4::dot(const vec4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float vec4::length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    vec4 vec4::normalized() const {
        float len = length();
        if (len > 0) {
            return vec4(x / len, y / len, z / len, w / len);
        }
        return vec4();
    }

    std::ostream& operator<<(std::ostream& os, const vec4& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
        return os;
    }
}