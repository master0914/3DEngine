//
// Created by User on 05.08.2025.
//

#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <vector>

#include "Renderer_2D.h"

#endif //MESH_H
#pragma once
#include "VectorUtil.h"

namespace Engine {
    struct Vertex {
        Engine::vec3 position;
        Engine::vec2 texCoord;
        Engine::vec3 normal;

        void debugPrint() const{
            std::cout << "position(" << position.getX() << ", " << position.getY() << ", " << position.getZ() << ")\n";
            std::cout << "texCoord(" << texCoord.getX() << ", " << texCoord.getY() << ")\n";
            std::cout << "normal(" << normal.getX() << ", " << normal.getY() << ", " << normal.getZ() << ")\n";
        }
    };

    struct Triangle {
        Vertex vertices[3];

        void debugPrint() const{
            for(int i = 0; i < 3; i++){
                std::cout << this;
                std::cout << "vertex: " << i;
                vertices[i].debugPrint();
            }
        }
    };

    class Mesh {
    public:
        Mesh(const std::string& filepath);
        void loadFromOBJ(const std::string& filepath);
        void debugPrintData() const;
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