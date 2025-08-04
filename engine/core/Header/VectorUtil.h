//
// Created by User on 04.08.2025.
//

#ifndef VECTORUTIL_H
#define VECTORUTIL_H
#include <ostream>

#endif //VECTORUTIL_H
#pragma once

namespace Engine {
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
    private:
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
    private:
        float x, y;
    };
}
