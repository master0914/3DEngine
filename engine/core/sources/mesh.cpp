//
// Created by User on 05.08.2025.
//
#include <string>
#include "../Header/mesh.h"
#include "../Header/debug.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

namespace Engine {



    std::ostream& operator<<(std::ostream& os, const Vertex& v){
        os << "Vertex: " << &v << "\n";
        os << "\tposition(" << v.position.getX() << ", " << v.position.getY() << ", " << v.position.getZ() << ")\n";
        os << "\ttexCoord(" << v.texCoord.getX() << ", " << v.texCoord.getY() << ")\n";
        os << "\tnormal(" << v.normal.getX() << ", " << v.normal.getY() << ", " << v.normal.getZ() << ")\n";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const Triangle& triangle){
        os << "Triangle: " << &triangle << "\n";
        for (int i = 0; i < 3; i++) {
            os << "\tvertex " << i << " = " << triangle.vertices[i] << "\n";
        }
        return os;
    }



    Mesh::Mesh(const std::string& filepath) {
        DEBUG_PRINT("Mesh created \n");
        loadFromOBJ(filepath);
    }
    void Mesh::loadFromOBJ(const std::string& filepath) {
        // datei laden
        std::ifstream file(filepath);
        if (!file.is_open()){std::cerr << "loading obj-file failed" << "\n";return;}

        std::vector<Engine::vec3> temp_positions;  // Speichert alle "v"-Einträge
        std::vector<Engine::vec3> temp_normals;   // Speichert alle "vn"-Einträge
        std::map<std::pair<unsigned int, unsigned int>, unsigned int> vertexCache; // vertex cache um duplikate vertices zu vermeiden

        std::string line;
        // geht alle lines in einer while loop durch
        while (std::getline(file,line)) {
            // nimmt ersten token   (#,v,vn,vt,f)
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type.empty() || type == "#" || type == "####") continue;
            else if (type == "v") {
                float x,y,z;
                iss >> x >> y >> z;
//                std::cout << "parsing v line:" << "\n";
//                std::cout << line << "\n";
//                std::cout << "found data: "<< x << ", " << y << ", " << z << "\n";
                temp_positions.push_back(Engine::vec3(x,y,z));
            }
            else if (type == "vn"){
                float x,y,z;
                iss >> x >> y >> z;
//                std::cout << "parsing vn line:" << "\n";
//                std::cout << line << "\n";
//                std::cout << "found data: "<< x << ", " << y << ", " << z << "\n";
                temp_normals.push_back(Engine::vec3(x,y,z));}
            else if (type == "f") {
                std::string faceToken;
                std::vector<unsigned int> faceIndices;
                for (int i = 0; i < 3; ++i) {
                    iss >> faceToken;

                    // Zerlege "v//vn" in vIdx und nIdx
                    size_t slash1 = faceToken.find('/');
                    size_t slash2 = faceToken.find('/', slash1 + 1);

                    unsigned int vIdx = std::stoi(faceToken.substr(0, slash1));
                    unsigned int nIdx = std::stoi(faceToken.substr(slash2 + 1));

                    // Erstelle einen eindeutigen Key für die Kombination (vIdx, nIdx)
                    auto vertexKey = std::make_pair(vIdx, nIdx);

                    // Prüfe, ob dieser Vertex bereits existiert
                    if (vertexCache.find(vertexKey) == vertexCache.end()) {
                        // Neuer Vertex -> erstellen und in Cache speichern
                        Vertex vertex;
                        vertex.position = temp_positions[vIdx - 1];
                        vertex.normal = temp_normals[nIdx - 1];
                        vertex.texCoord = Engine::vec2(); // Default, falls keine Texturkoordinaten

                        vertices.push_back(vertex);
                        vertexCache[vertexKey] = vertices.size() - 1;
                    }

                    // Index hinzufügen (entweder neu oder aus Cache)
                    faceIndices.push_back(vertexCache[vertexKey]);
                }
                indices.insert(indices.end(), faceIndices.begin(), faceIndices.end());
            }
        }
        processData();
        //debugprint();
    }

    void Mesh::processData() {
        triangles.clear();

        for(size_t i = 0; i < indices.size();i += 3){
            Triangle tri;

            tri.vertices[0] =vertices[indices[i]];
            tri.vertices[1] =vertices[indices[i+1]];
            tri.vertices[2] =vertices[indices[i+2]];

//            DEBUG_PRINT("Triangle " << i/3 << ":");
//            DEBUG_PRINT("  v0: " << tri.vertices[0].position.x << ", "
//                                 << tri.vertices[0].position.y << ", "
//                                 << tri.vertices[0].position.z);
//            DEBUG_PRINT("  v1: " << tri.vertices[1].position.x << ", "
//                                 << tri.vertices[1].position.y << ", "
//                                 << tri.vertices[1].position.z);
//            DEBUG_PRINT("  v2: " << tri.vertices[2].position.x << ", "
//                                 << tri.vertices[2].position.y << ", "
//                                 << tri.vertices[2].position.z);
//            DEBUG_PRINT("");

            triangles.push_back(tri);
        }
    }

    void Mesh::debugprint() const {
        std::cout << "Mesh Debug Info:\n";
        std::cout << "  Vertex Count: " << vertices.size() << "\n";
        std::cout << "  Index Count:  " << indices.size() << "\n";

        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << "Vertex " << i << "  " << &vertices << ":\n";
            std::cout << vertices[i] << "\n";
        }

        std::cout << "Triangles: \n";
        for (size_t i = 0; i < triangles.size(); ++i) {
            std::cout << "Triangle " << i << ":\n";
            std::cout << triangles[i] << "\n";
        }
    }


}
