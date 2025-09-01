//
// Created by Master0914 on 01.09.2025.
//
#pragma once
#include "../Header/Renderer_3D.h"

namespace Engine{
        void Renderer_3D::beginFrame() {
            m_RenderQueue.clear();
            std::fill(m_FrameBuffer.begin(), m_FrameBuffer.end(), 0xff000000);   //Framebuffer wird auf hintergrundfarbe gesetzt
            std::fill(m_DepthBuffer.begin(), m_DepthBuffer.end(), 1.0f);
        };

        void Renderer_3D::submit(const Mesh &mesh, const mat4 &transform){
            m_RenderQueue.push_back({&mesh, transform});
        };

        void Renderer_3D::endFrame(){
            for(RenderCommand& command: m_RenderQueue){
                //MVP-Matrix:
                //Model: command.transform
                //View: camera.getViewMatrix
                //Projection: camera.getProjectionMatrix
                mat4 mvpMatrix = camera->getProjectionMatrix() * camera->getViewMatrix() * command.transform;
                rasterizeMesh(*command.mesh, mvpMatrix);
            }
            //frameBuffer Zeichnen
        };

        void Renderer_3D::setCamera(Camera &camera){
            this->camera = &camera;
        };

    void Renderer_3D::rasterizeMesh(const Mesh& mesh, const mat4& mvpMatrix) {
        // Hier kommt dein kompletter Rasterisierungsalgorithmus hin!
        // Für jedes Dreieck im Mesh:
        const std::vector<Triangle>& meshTriangles = mesh.getTriangles();

        for (const Triangle& triangle : meshTriangles) {
            triangle.debugPrint();
            // - Transformiere alle 3 Vertices mit der mvpMatrix
            // - Führe den Perspective Divide durch (x/w, y/w, z/w)
            // - Führe Clipping durch (optional, aber wichtig für Stabilität)
            // - Mappe die homogenen Koordinaten (-1 to 1) auf Screen-Koordinaten (0 to width/height) um
            // - Rasterisiere das Dreieck (deine draw_triangle Funktion)
            //   Übergib dabei die transformierten Koordinaten und den Z-Wert für den Depth-Test
        }
    }

}
