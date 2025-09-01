//
// Created by User on 04.08.2025.
//

#include "../Header/VectorUtil.h"

#include <ostream>
#include <valarray>

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


    //Matrix4-----------------------------------------------------------------------

    mat4 mat4::Perspective(float fovRadians, float aspect, float nearZ, float farZ) {
        float f = 1.0f / std::tan(fovRadians / 2.0f);
        mat4 P;
        P.m = { f/aspect, 0, 0, 0,
                0, f, 0, 0,
                0, 0, (farZ+nearZ)/(nearZ-farZ), -1,
                0, 0, (2*farZ*nearZ)/(nearZ-farZ), 0 };
        return P;
    }

    mat4 mat4::Orthographic(float left, float right, float bottom, float top, float nearZ, float farZ) {
        mat4 O;
        O.m = { 2.0f/(right-left), 0, 0, 0,
                0, 2.0f/(top-bottom), 0, 0,
                0, 0, -2.0f/(farZ-nearZ), 0,
                -(right+left)/(right-left),
                -(top+bottom)/(top-bottom),
                -(farZ+nearZ)/(farZ-nearZ),
                1 };
        return O;
    }

    mat4 mat4::LookAt(const vec3& eye, const vec3& center, const vec3& up) {
        vec3 f = (center - eye).normalized();
        vec3 s = f.cross(up).normalized();
        vec3 u = s.cross(f);

        mat4 V;
        V.m = { s.getX(), u.getX(), -f.getX(), 0,
                s.getY(), u.getY(), -f.getY(), 0,
                s.getZ(), u.getZ(), -f.getZ(), 0,
                -s.dot(eye), -u.dot(eye), f.dot(eye), 1 };
        return V;
    }














    // --- Konstruktoren ---
    mat4::mat4() : m{ 1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      0,0,0,1 } {}

    mat4::mat4(float diagonal) : m{ diagonal,0,0,0,
                                    0,diagonal,0,0,
                                    0,0,diagonal,0,
                                    0,0,0,diagonal } {}

    mat4::mat4(const std::array<float,16>& values) : m(values) {}

// --- Fabrikmethoden ---
    mat4 mat4::Identity() { return mat4(); }

    mat4 mat4::Translation(float tx, float ty, float tz) {
        mat4 T = mat4::Identity();
        T.m[12] = tx; // col=3,row=0 -> 3*4+0 = 12
        T.m[13] = ty; // col=3,row=1 -> 13
        T.m[14] = tz; // col=3,row=2 -> 14
        return T;
    }

    mat4 mat4::Scale(float sx, float sy, float sz) {
        mat4 S;
        S.m = { sx,0, 0, 0,
                0, sy,0, 0,
                0, 0, sz,0,
                0, 0, 0, 1 };
        return S;
    }

    mat4 mat4::RotationZ(float r) {
        const float c = std::cos(r);
        const float s = std::sin(r);
        mat4 R;
        R.m = {  c, s, 0, 0,   // Spalte 0
                 -s, c, 0, 0,   // Spalte 1
                 0, 0, 1, 0,   // Spalte 2
                 0, 0, 0, 1 }; // Spalte 3
        return R;
    }

// --- Multiplikation ---
    mat4 mat4::operator*(const mat4& rhs) const {
        mat4 out;
        // out(row, col) = sum_k this(row,k) * rhs(k,col)
        for (int col = 0; col < 4; ++col) {
            for (int row = 0; row < 4; ++row) {
                float sum = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    sum += at(row, k) * rhs.at(k, col);
                }
                out.at(row, col) = sum;
            }
        }
        return out;
    }

    mat4& mat4::operator*=(const mat4& rhs) {
        *this = *this * rhs;
        return *this;
    }

// --- 2D-Transform-Helfer ---
    vec2 mat4::transformPoint(const vec2& p) const {
        // v = (x,y,0,1)
        const float x = p.getX();
        const float y = p.getY();

        const float rx = at(0,0)*x + at(0,1)*y + at(0,2)*0.0f + at(0,3)*1.0f;
        const float ry = at(1,0)*x + at(1,1)*y + at(1,2)*0.0f + at(1,3)*1.0f;
        const float rw = at(3,0)*x + at(3,1)*y + at(3,2)*0.0f + at(3,3)*1.0f;

        if (std::abs(rw) > 1e-8f) {
            return vec2(rx / rw, ry / rw);
        }
        return vec2(rx, ry); // affine Fälle haben rw==1
    }

    vec2 mat4::transformDirection(const vec2& d) const {
        // v = (x,y,0,0)  -> ignoriert Translation
        const float x = d.getX();
        const float y = d.getY();

        const float rx = at(0,0)*x + at(0,1)*y;
        const float ry = at(1,0)*x + at(1,1)*y;
        return vec2(rx, ry);
    }

// --- Transponieren ---
    mat4 mat4::transposed() const {
        mat4 t;
        for (int col = 0; col < 4; ++col) {
            for (int row = 0; row < 4; ++row) {
                t.at(row, col) = at(col, row);
            }
        }
        return t;
    }

// --- Determinante (generisch 4x4, Laplace / Block-Ausdrücke) ---
    static inline float det3(
            float a00,float a01,float a02,
            float a10,float a11,float a12,
            float a20,float a21,float a22)
    {
        return a00*(a11*a22 - a12*a21)
               - a01*(a10*a22 - a12*a20)
               + a02*(a10*a21 - a11*a20);
    }

    float mat4::determinant() const {
        // Zerlege nach erster Zeile (row 0), beachte column-major Indizierung
        // Für Lesbarkeit holen wir die 4x4 in r/c-Form:
        float a00 = at(0,0), a01 = at(0,1), a02 = at(0,2), a03 = at(0,3);
        float a10 = at(1,0), a11 = at(1,1), a12 = at(1,2), a13 = at(1,3);
        float a20 = at(2,0), a21 = at(2,1), a22 = at(2,2), a23 = at(2,3);
        float a30 = at(3,0), a31 = at(3,1), a32 = at(3,2), a33 = at(3,3);

        float m0 = det3(a11,a12,a13,  a21,a22,a23,  a31,a32,a33);
        float m1 = det3(a10,a12,a13,  a20,a22,a23,  a30,a32,a33);
        float m2 = det3(a10,a11,a13,  a20,a21,a23,  a30,a31,a33);
        float m3 = det3(a10,a11,a12,  a20,a21,a22,  a30,a31,a32);

        return a00*m0 - a01*m1 + a02*m2 - a03*m3;
    }

// --- Inverse (allgemein 4x4, Cofactors / Adjunct) ---
    mat4 mat4::inverted() const {
        const float a00 = at(0,0), a01 = at(0,1), a02 = at(0,2), a03 = at(0,3);
        const float a10 = at(1,0), a11 = at(1,1), a12 = at(1,2), a13 = at(1,3);
        const float a20 = at(2,0), a21 = at(2,1), a22 = at(2,2), a23 = at(2,3);
        const float a30 = at(3,0), a31 = at(3,1), a32 = at(3,2), a33 = at(3,3);

        mat4 inv;
        auto& o = inv.m;

        o[0]  =  det3(a11,a12,a13, a21,a22,a23, a31,a32,a33);
        o[1]  = -det3(a10,a12,a13, a20,a22,a23, a30,a32,a33);
        o[2]  =  det3(a10,a11,a13, a20,a21,a23, a30,a31,a33);
        o[3]  = -det3(a10,a11,a12, a20,a21,a22, a30,a31,a32);

        o[4]  = -det3(a01,a02,a03, a21,a22,a23, a31,a32,a33);
        o[5]  =  det3(a00,a02,a03, a20,a22,a23, a30,a32,a33);
        o[6]  = -det3(a00,a01,a03, a20,a21,a23, a30,a31,a33);
        o[7]  =  det3(a00,a01,a02, a20,a21,a22, a30,a31,a32);

        o[8]  =  det3(a01,a02,a03, a11,a12,a13, a31,a32,a33);
        o[9]  = -det3(a00,a02,a03, a10,a12,a13, a30,a32,a33);
        o[10] =  det3(a00,a01,a03, a10,a11,a13, a30,a31,a33);
        o[11] = -det3(a00,a01,a02, a10,a11,a12, a30,a31,a32);

        o[12] = -det3(a01,a02,a03, a11,a12,a13, a21,a22,a23);
        o[13] =  det3(a00,a02,a03, a10,a12,a13, a20,a22,a23);
        o[14] = -det3(a00,a01,a03, a10,a11,a13, a20,a21,a23);
        o[15] =  det3(a00,a01,a02, a10,a11,a12, a20,a21,a22);

        const float det = a00*o[0] + a01*o[1] + a02*o[2] + a03*o[3];
        if (std::abs(det) < 1e-8f) {
            // Nicht invertierbar – hier defensiv Identity zurückgeben.
            // (Alternativ: Exception werfen)
            return mat4::Identity();
        }
        const float invDet = 1.0f / det;
        for (float& v : inv.m) v *= invDet;
        return inv;
    }

// --- Debug-Ausgabe ---
    std::ostream& operator<<(std::ostream& os, const mat4& M) {
        os << std::fixed << std::setprecision(3);
        for (int r = 0; r < 4; ++r) {
            os << "| ";
            for (int c = 0; c < 4; ++c) {
                os << std::setw(8) << M.at(r, c) << " ";
            }
            os << "|\n";
        }
        return os;
    }
}
