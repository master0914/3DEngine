//
// Created by User on 04.08.2025.
//

#ifndef VECTORUTIL_H
#define VECTORUTIL_H
#include <ostream>
#include <array>

#endif //VECTORUTIL_H
#pragma once

namespace Engine {
    class vec4 {
    public:
        float x, y, z, w;

        vec4();
        vec4(float x, float y, float z, float w);

        vec4 operator+(const vec4& other) const;
        vec4 operator-(const vec4& other) const;
        vec4 operator*(float scalar) const;
        float dot(const vec4& other) const;
        float length() const;
        vec4 normalized() const;

        friend std::ostream& operator<<(std::ostream& os, const vec4& v);
    };
    class vec3 {
    public:
        // Konstruktoren
        vec3();
        vec3(float x, float y, float z);

        // Vektoraddition
        vec3 operator+(const vec3& other) const;

        // Vektorsubtraktion
        vec3 operator-(const vec3& other) const;

        // Skalarmultiplikation
        vec3 operator*(float scalar) const;

        // Skalarprodukt (Dot Product)
        float dot(const vec3& other) const;

        // Kreuzprodukt (Cross Product)
        vec3 cross(const vec3& other) const ;

        // Vektorlänge (Magnitude)
        float length() const;

        // Normalisierter Vektor
        vec3 normalized() const;

        // Ausgabe (für Debugging)
        friend std::ostream& operator<<(std::ostream& os, const vec3& v);

        float getX() const{return x;}
        float getY() const{return y;}
        float getZ() const{return z;}

        float x, y, z;
    };
    class vec2 {
    public:
        // Konstruktoren
        vec2();
        vec2(float x, float y);

        // Vektoraddition
        vec2 operator+(const vec2& other) const;

        // Vektorsubtraktion
        vec2 operator-(const vec2& other) const;

        // Skalarmultiplikation
        vec2 operator*(float scalar) const;

        // Skalarprodukt (Dot Product)
        float dot(const vec2& other) const;

        // Vektorlänge (Magnitude)
        float length() const;

        // Normalisierter Vektor
        vec2 normalized() const;

        // Ausgabe (für Debugging)
        friend std::ostream& operator<<(std::ostream& os, const vec2& v);

        float getX() const{return x;}
        float getY() const{return y;}

        float x, y;
    };
    // danke ChatGPT:

    // 4x4-Matrix, COLUMN-MAJOR Layout (OpenGL-Style):
    // Index: m[col*4 + row]
    class mat4 {
    public:
        // --- Daten ---
        // Zugriff: m[c*4 + r]  (c=Spalte 0..3, r=Zeile 0..3)
        std::array<float, 16> m{};

        // --- Konstruktoren ---
        mat4();                                 // Identity
        explicit mat4(float diagonal);          // Diagonalmatrix (diagonal auf diag)
        explicit mat4(const std::array<float,16>& values); // Rohwerte (column-major)


        static mat4 LookAt(const vec3& eye, const vec3& center, const vec3& up);





        // --- Fabrikmethoden / Hilfs-Erzeuger ---
        static mat4 Identity();
        static mat4 Zero();
        static mat4 Translation(float tx, float ty, float tz = 0.0f);
        static mat4 Scale(float sx, float sy, float sz = 1.0f);
        static mat4 RotationZ(float radians);

        // --- Basisoperationen ---
        mat4 operator*(const mat4& rhs) const;  // Matrixmultiplikation
        vec4 operator*(const vec4& v) const;    // Matrix-Vector Multiplikation
        mat4& operator*=(const mat4& rhs);

        // Punkt-/Richtungs-Transformationen (2D bequem mit homogener Einbettung)
        vec2 transformPoint(const vec2& p) const;      // (x,y,0,1)
        vec2 transformDirection(const vec2& d) const;  // (x,y,0,0)  (keine Translation)

        // Transponieren
        mat4 transposed() const;

        // Determinante & Inverse (voll 4x4)
        float determinant() const;
        mat4 inverted() const;        // wirft bei singulärer Matrix per Fallback eine Identität zurück (siehe Doku)

        // Index-Helfer (row, col): 0..3
        float  operator()(int row, int col) const { return m[col * 4 + row]; }
        float& operator()(int row, int col)       { return m[col * 4 + row]; }
        float  at(int row, int col) const { return m[col * 4 + row]; }
        float& at(int row, int col)       { return m[col * 4 + row]; }

        // Debug-Ausgabe
        friend std::ostream& operator<<(std::ostream& os, const mat4& M);
    };
}
