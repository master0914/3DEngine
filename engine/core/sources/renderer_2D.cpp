//
// Created by User on 04.08.2025.
//

#include <iostream>
#include "../Header/renderer_2D.h"

namespace Engine {
    void Renderer_2D::drawRectangle(Window& window, vec2& origin, int height, int width, uint32_t color){}
    void Renderer_2D::fillRectangle(Window& window, vec2& origin, int height, int width, uint32_t color){}
    void Renderer_2D::drawCircle(Window& window, vec2& middle, int radius, uint32_t color){}
    void Renderer_2D::fillCircle(Window& window, vec2& middle, int radius, uint32_t color){}
    void Renderer_2D::drawTriangle(Window& window, vec2& p1, vec2& p2, vec2& p3, uint32_t color) {
        std::cout << "drawing triangle: \n" << p1 << p2 << p3 << "\n";
        drawLine(window, p1,p2,color);
        drawLine(window, p2,p3,color);
        drawLine(window, p1,p3,color);
    }
    void Renderer_2D::drawLine(Window& window, vec2& p1, vec2& p2, uint32_t color) {
        int x0 = static_cast<int>(p1.getX());
        int y0 = static_cast<int>(p1.getY());
        int x1 = static_cast<int>(p2.getX());
        int y1 = static_cast<int>(p2.getY());
        std::cout << "with coordinates: \n" << x0 << "  "<< y0 << "  "<< x1 << "  "<< y1 << "  ";
        // Sonderfall: Punkt
        if (x0 == x1 && y0 == y1) {
            window.DrawPixel(x0, y0, color);
            return;
        }

        // Sonderfall: Vertikale Linie
        if (x0 == x1) {
            if (y0 > y1) std::swap(y0, y1);
            for (int y = y0; y <= y1; y++) {
                window.DrawPixel(x0, y, color);
            }
            return;
        }

        // Sonderfall: Horizontale Linie
        if (y0 == y1) {
            if (x0 > x1) std::swap(x0, x1);
            for (int x = x0; x <= x1; x++) {
                window.DrawPixel(x, y0, color);
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
            window.DrawPixel(x0, y0, color);
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
    void Renderer_2D::drawLine(std::vector<uint32_t>& buffer, int w, int h, vec2& p1, vec2& p2, uint32_t color){

        int x0 = static_cast<int>(p1.getX());
        int y0 = static_cast<int>(p1.getY());
        int x1 = static_cast<int>(p2.getX());
        int y1 = static_cast<int>(p2.getY());
        // Sonderfall: Punkt
        if (x0 == x1 && y0 == y1) {
            drawPixelToBuffer(buffer, w, h, x0, y0, color);
            return;
        }

        // Sonderfall: Vertikale Linie
        if (x0 == x1) {
            if (y0 > y1) std::swap(y0, y1);
            for (int y = y0; y <= y1; y++) {
                drawPixelToBuffer(buffer, w, h, x0, y, color);
            }
            return;
        }

        // Sonderfall: Horizontale Linie
        if (y0 == y1) {
            if (x0 > x1) std::swap(x0, x1);
            for (int x = x0; x <= x1; x++) {
                drawPixelToBuffer(buffer, w, h, x, y0, color);
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
            drawPixelToBuffer(buffer, w, h, x0, y0, color);
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

    void Renderer_2D::drawLine(std::vector<uint32_t>& buffer, int w, int h, int x0,int y0, int x1, int y1, uint32_t color){

        // Sonderfall: Punkt
        if (x0 == x1 && y0 == y1) {
            drawPixelToBuffer(buffer, w, h, x0, y0, color);
            return;
        }

        // Sonderfall: Vertikale Linie
        if (x0 == x1) {
            if (y0 > y1) std::swap(y0, y1);
            for (int y = y0; y <= y1; y++) {
                drawPixelToBuffer(buffer, w, h, x0, y, color);
            }
            return;
        }

        // Sonderfall: Horizontale Linie
        if (y0 == y1) {
            if (x0 > x1) std::swap(x0, x1);
            for (int x = x0; x <= x1; x++) {
                drawPixelToBuffer(buffer, w, h, x, y0, color);
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
            drawPixelToBuffer(buffer, w, h, x0, y0, color);
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

    void Renderer_2D::drawTriangleWireFrame(std::vector<uint32_t>& buffer, int w, int h, vec3& v0, vec3& v1, vec3& v2, uint32_t color){
        std::cout << "Line from (" << v0.x << "," << v0.y << ") to (" << v1.x << "," << v1.y << ")\n";
        drawLine(buffer,w,h,static_cast<int>(v0.x), static_cast<int>(v0.y),
                 static_cast<int>(v1.x), static_cast<int>(v1.y), color);
        std::cout << "Line from (" << v1.x << "," << v1.y << ") to (" << v2.x << "," << v2.y << ")\n";
        drawLine(buffer,w,h,static_cast<int>(v1.x), static_cast<int>(v1.y),
                 static_cast<int>(v2.x), static_cast<int>(v2.y), color);
        std::cout << "Line from (" << v2.x << "," << v2.y << ") to (" << v0.x << "," << v0.y << ")\n";
        drawLine(buffer,w,h,static_cast<int>(v2.x), static_cast<int>(v2.y),
                 static_cast<int>(v0.x), static_cast<int>(v0.y), color);
    }

    void Renderer_2D::drawPixelToBuffer(std::vector<uint32_t> &buffer, int w, int h, int x, int y, uint32_t color) {
        if (x < 0 || x >= w || y < 0 || y >= h) {
            std::cout << "Renderer: ERROR: Tried to draw out of bounds pixel \n";
            return;
        }
        buffer.at(y * w + x) = color;
    }
}


// alte bresham algorithmen:
//
//        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
//
//        if (steep) {
//            std::swap(x0, y0);
//            std::swap(x1, y1);
//        }
//
//        if (x0 > x1) {
//            std::swap(x0, x1);
//            std::swap(y0, y1);
//        }
//
//        int dx = x1 - x0;
//        int dy = std::abs(y1 - y0);
//        int error = 0;
//        int ystep = (y0 < y1) ? 1 : -1;
//        int y = y0;
//
//        for (int x = x0; x <= x1; x++) {
//            if (steep) {
//                window.DrawPixel(y, x, color);
//            } else {
//                window.DrawPixel(x, y, color);
//            }
//
//            error -= dy;
//            if (error < 0) {
//                y += ystep;
//                error += dx;
//            }
//        }





//        int dx = abs(x0 - x1), dy = abs(y0 - y1);
//        int p = 2*dy - dx;
//        int twoDy = 2*dy, twoDyDx = 2*(dy - dx);
//        int x, y, xEnd;
//        /*Determine which points to start and End */
//        if(x0>x1){
//            x = x1;
//            y = y1;
//            xEnd = x0;
//        }
//        else{
//            x = x0; y = y0 ; xEnd =  x1;
//        }
//        window.DrawPixel(x, y, color);
//        while(x < xEnd){
//            x++;
//            if(p<0){
//                p = p + twoDy;
//            }
//            else{
//                y++;
//                p = p + twoDyDx;
//            }
//            window.DrawPixel(x, y, color);
//        }