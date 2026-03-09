//
// Created by User on 05.08.2025.
//

#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <vector>

#include "../General/renderer_2D.h"

#endif //MESH_H
#pragma once
// #include "../../math/Vectors/VectorUtil.h"

namespace Engine {
    struct Vertex {
        vec3 position;
        vec2 texCoord;
        vec3 normal;
    };

    struct Triangle {
        Vertex vertices[3];
    };



    std::ostream& operator<<(std::ostream& os, const Vertex& v);
    std::ostream& operator<<(std::ostream& os, const Triangle& triangle);

    class Mesh {
    public:
        Mesh(const std::string& filepath);
        void loadFromOBJ(const std::string& filepath);
        void debugprint() const;
        std::vector<Triangle> getTriangles() const{
            return triangles;
        }
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Triangle> triangles;

        void processData();
    };
}