//
// Created by Master0914 on 01.09.2025.
//

#ifndef INC_3DENGINE_RENDERER_3D_H
#define INC_3DENGINE_RENDERER_3D_H

#endif //INC_3DENGINE_RENDERER_3D_H

#pragma once
#include <vector>
#include "Camera.h"
#include "mesh.h"
#include "VectorUtil.h"
#include "Camera.h"

namespace Engine {
    struct RenderCommand{
        const Mesh* mesh;
        mat4 transform;
    };

    class Renderer_3D {
    public:
        void beginFrame(); // Cleart Buffer, setzt Zeit, etc.
        void submit(const Mesh &mesh,const mat4 &transform); // Fügt ein Objekt zur Render-Queue hinzu     @TODO material etc
        void endFrame(); // Führt alle Draw-Calls aus, swapped Buffer
        void setCamera( Camera &camera); // Setzt die aktuelle Kamera
    private:
        void rasterizeMesh(const Mesh& mesh, const mat4& mvpMatrix);

        std::vector<RenderCommand> m_RenderQueue; // Liste aller zu rendernden Objekte
        std::vector<uint32_t> m_FrameBuffer;
        std::vector<float> m_DepthBuffer;
        Camera* camera;
    };
}