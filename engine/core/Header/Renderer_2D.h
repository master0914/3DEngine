//
// Created by User on 04.08.2025.
//

#ifndef RENDERER_2D_H
#define RENDERER_2D_H
#include <cstdint>

#include "../../window/Window.h"
#include "../Header/VectorUtil.h"

#endif //RENDERER_2D_H
#pragma once

namespace Engine {
    class Renderer_2D {
    public:
        void drawRectangle(Window& window, vec2& origin, int height, int width, uint32_t color);
        void fillRectangle(Window& window, vec2& origin, int height, int width, uint32_t color);
        void drawCricle(Window& window, vec2& middle, int radius, uint32_t color);
        void fillCricle(Window& window, vec2& middle, int radius, uint32_t color);
        void drawTriangle(Window&, vec2& p1, vec2& p2, vec2& p3, uint32_t color);
        void drawLine(Window& window, vec2& p1, vec2& p2, uint32_t color);
    };
}