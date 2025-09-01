//
// Created by User on 04.08.2025.
//

#ifndef RENDERER_2D_H
#define RENDERER_2D_H
#include <cstdint>

#include "../../window/Window.h"
#include "../../Math/Vectors/VectorUtil.h"

#endif //RENDERER_2D_H
#pragma once

namespace Engine {
    class Renderer_2D {
    public:
        void drawRectangle(Window& window, vec2& origin, int height, int width, uint32_t color);
        void fillRectangle(Window& window, vec2& origin, int height, int width, uint32_t color);
        void drawCircle(Window& window, vec2& middle, int radius, uint32_t color);
        void fillCircle(Window& window, vec2& middle, int radius, uint32_t color);
        void drawTriangle(Window&, vec2& p1, vec2& p2, vec2& p3, uint32_t color);
        void drawLine(Window& window, vec2& p1, vec2& p2, uint32_t color);
        void drawLine(std::vector<uint32_t>& buffer, int w, int h, vec2& p1, vec2& p2, uint32_t color);
        void drawLine(std::vector<uint32_t>& buffer, int w, int h, int x1,int y1, int x2, int y2, uint32_t color);
        void drawTriangleWireFrame(std::vector<uint32_t>& buffer, int w, int h, vec3& p1, vec3& p2, vec3& p3, uint32_t color);
        void drawPixelToBuffer(std::vector<uint32_t>& buffer, int w, int h, int x, int y, uint32_t color);
    };
}