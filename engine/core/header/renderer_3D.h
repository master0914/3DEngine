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

namespace Engine {
    struct RenderCommand{
        const Mesh* mesh;
        mat4 transform;
    };

    class Renderer_3D {
    public:
        explicit Renderer_3D(Window& window);

        void beginFrame(); // Cleart Buffer, setzt Zeit, etc.

        void submit(const Mesh &mesh,const mat4 &transform); // Fügt ein Objekt zur Render-Queue hinzu     @TODO material etc

        void present();
        void endFrame(); // Führt alle Draw-Calls aus, swapped Buffer

        void setCamera( Camera &camera); // Setzt die aktuelle Kamera

        void setBackGroundColor(uint32_t color){backGroundColor = color;}
        void setRenderColor(uint32_t color){renderColor = color;}
    private:
        void rasterizeMesh(const Mesh& mesh, const mat4& mvpMatrix);
        void clearBuffer();

        Window* window;
        Renderer_2D renderer2D;
        std::vector<RenderCommand> m_RenderQueue; // Liste aller zu rendernden Objekte
        std::vector<uint32_t> m_FrameBuffer;
        std::vector<float> m_DepthBuffer;
        int m_width, m_height;
        Camera* camera;
        uint32_t backGroundColor;
        uint32_t renderColor;
    };
}