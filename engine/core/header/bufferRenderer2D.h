//
// Created by Master0914 on 19.09.2025.
//

#ifndef INC_3DENGINE_BUFFERRENDERER2D_H
#define INC_3DENGINE_BUFFERRENDERER2D_H

#endif //INC_3DENGINE_BUFFERRENDERER2D_H
#pragma once
#include <cstdint>
#include "../../math/Vectors/VectorUtil.h"
namespace Engine {
    class BufferRenderer2D {
    public:
        void setTargetBuffer(uint32_t *buffer, int width, int height) {
            m_buffer = buffer;
            m_width = width;
            m_height = height;
        }

        void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
        void drawTriangleWireFrame(vec3 &v0, vec3 &v1, vec3 &v2, uint32_t color);

        inline void drawPixelToBuffer(uint32_t* buffer, int width, int height,
                                                   int x, int y, uint32_t color) {

            if (x < 0 || x >= width || y < 0 || y >= height) return;
            buffer[y * width + x] = color;
        }

    private:
        uint32_t *m_buffer = nullptr;
        int m_width = 0;
        int m_height = 0;

    };
}