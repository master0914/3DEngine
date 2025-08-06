//
// Created by User on 05.08.2025.
//

#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <vector>

#include "../Header/Renderer_2D.h"

#endif //MESH_H
#pragma once
#include "../Header/VectorUtil.h"

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

    class Mesh {
    public:
        Mesh(const std::string& filepath);
        void loadFromOBJ(const std::string& filepath);
        void debugPrintData() const;
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };
}