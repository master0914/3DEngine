//
// Created by Master0914 on 01.09.2025.
//

#ifndef INC_3DENGINE_RENDERER_3D_H
#define INC_3DENGINE_RENDERER_3D_H

#endif //INC_3DENGINE_RENDERER_3D_H

#pragma once
#include <vector>
#include "camera.h"
#include "mesh.h"
#include "../../Math/Vectors/VectorUtil.h"
#include "camera.h"
#include "renderer_2D.h"
#include "bufferRenderer2D.h"

namespace Engine {
    struct RenderCommand{
        const Mesh* mesh;
        mat4 transform;
    };

    class Renderer_3D {
        //TODO: depthbuffer
    public:
        explicit Renderer_3D(Window& window);

        void beginFrame(); // Cleart Buffer, setzt Zeit, etc.

        void submit(const Mesh &mesh,const mat4 &transform); // Fügt ein Objekt zur Render-Queue hinzu     @TODO material etc

        void present();
        void endFrame(); // Führt alle Draw-Calls aus, swapped Buffer

        void setCamera( Camera &camera); // Setzt die aktuelle Kamera

        void setPixel(int x, int y, uint32_t color);
        void setPixel(int x, int y, float z, uint32_t color); // Mit Z-Test

        void setBackGroundColor(uint32_t color){backGroundColor = color;}
        void setRenderColor(uint32_t color){renderColor = color;}
    private:
        void renderMesh(const Mesh& mesh, const mat4& transform);
        void rasterizeMesh(const Mesh& mesh, const mat4& mvpMatrix);
        void clearBuffer();

        // referenzen
        Window* window;
//        Renderer_2D renderer2D;
        BufferRenderer2D renderer2D{};

        std::vector<RenderCommand> m_RenderQueue; // Liste aller zu rendernden Objekte
        // Buffer
        std::vector<uint32_t> m_FrameBufferBack;
        std::vector<float> m_DepthBufferBack;
        std::vector<uint32_t> m_FrameBufferFront;
        int m_width, m_height;

        Camera* camera;

        uint32_t backGroundColor;
        uint32_t renderColor;
    };

    inline void Renderer_3D::setPixel(int x, int y, uint32_t color) {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            m_FrameBufferBack[y * m_width + x] = color;
        }
    }

    inline void Renderer_3D::setPixel(int x, int y, float z, uint32_t color) {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            if (z < m_DepthBufferBack[y * m_width + x]) {
                m_DepthBufferBack[y * m_width + x] = z;
                m_FrameBufferBack[y * m_width + x] = color;
            }
        }
    }
}