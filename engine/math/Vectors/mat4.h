//
// Created by augus on 07.03.2026.
//

#ifndef INC_3DENGINE_MAT4_H
#define INC_3DENGINE_MAT4_H
#include <array>

#include "vector.h"

#endif //INC_3DENGINE_MAT4_H

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