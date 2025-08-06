//
// Created by User on 04.08.2025.
//

#include "../Header/Renderer_2D.h"

namespace Engine {
    void Renderer_2D::drawRectangle(Window& window, vec2& origin, int height, int width, uint32_t color){}
    void Renderer_2D::fillRectangle(Window& window, vec2& origin, int height, int width, uint32_t color){}
    void Renderer_2D::drawCircle(Window& window, vec2& middle, int radius, uint32_t color){}
    void Renderer_2D::fillCircle(Window& window, vec2& middle, int radius, uint32_t color){}
    void Renderer_2D::drawTriangle(Window& window, vec2& p1, vec2& p2, vec2& p3, uint32_t color) {
        drawLine(window, p1,p2,color);
        drawLine(window, p2,p3,color);
        drawLine(window, p1,p3,color);
    }
    void Renderer_2D::drawLine(Window& window, vec2& p1, vec2& p2, uint32_t color) {
        int x0 = static_cast<int>(p1.getX());
        int y0 = static_cast<int>(p1.getY());
        int x1 = static_cast<int>(p2.getX());
        int y1 = static_cast<int>(p2.getY());

        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

        if (steep) {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int dx = x1 - x0;
        int dy = std::abs(y1 - y0);
        int error = dx / 2;
        int ystep = (y0 < y1) ? 1 : -1;
        int y = y0;

        for (int x = x0; x <= x1; x++) {
            if (steep) {
                window.DrawPixel(y, x, color);
            } else {
                window.DrawPixel(x, y, color);
            }

            error -= dy;
            if (error < 0) {
                y += ystep;
                error += dx;
            }
        }
    }
}