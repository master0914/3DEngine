//
// Created by Master0914 on 19.09.2025.
//

#include <iostream>
#include "../header/bufferRenderer2D.h"
namespace Engine{
    void BufferRenderer2D::drawLine(int x0,int y0, int x1, int y1, uint32_t color){

        // Sonderfall: Punkt
        if (x0 == x1 && y0 == y1) {
            drawPixelToBuffer(m_buffer, m_width, m_height, x0, y0, color);
            return;
        }

        // Sonderfall: Vertikale Linie
        if (x0 == x1) {
            if (y0 > y1) std::swap(y0, y1);
            for (int y = y0; y <= y1; y++) {
                drawPixelToBuffer(m_buffer, m_width, m_height, x0, y, color);
            }
            return;
        }

        // Sonderfall: Horizontale Linie
        if (y0 == y1) {
            if (x0 > x1) std::swap(x0, x1);
            for (int x = x0; x <= x1; x++) {
                drawPixelToBuffer(m_buffer, m_width, m_height, x, y0, color);
            }
            return;
        }

        // Normale diagonale Linie - Bresenham Algorithmus
        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            drawPixelToBuffer(m_buffer, m_width, m_height, x0, y0, color);
            if (x0 == x1 && y0 == y1) break;

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    void BufferRenderer2D::drawTriangleWireFrame(vec3& v0, vec3& v1, vec3& v2, uint32_t color){
//        std::cout << "Line from (" << v0.x << "," << v0.y << ") to (" << v1.x << "," << v1.y << ")\n";
        drawLine(static_cast<int>(v0.x), static_cast<int>(v0.y),
                 static_cast<int>(v1.x), static_cast<int>(v1.y), color);
//        std::cout << "Line from (" << v1.x << "," << v1.y << ") to (" << v2.x << "," << v2.y << ")\n";
        drawLine(static_cast<int>(v1.x), static_cast<int>(v1.y),
                 static_cast<int>(v2.x), static_cast<int>(v2.y), color);
//        std::cout << "Line from (" << v2.x << "," << v2.y << ") to (" << v0.x << "," << v0.y << ")\n";
        drawLine(static_cast<int>(v2.x), static_cast<int>(v2.y),
                 static_cast<int>(v0.x), static_cast<int>(v0.y), color);
    }

}
