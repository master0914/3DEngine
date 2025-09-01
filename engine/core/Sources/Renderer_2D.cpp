//
// Created by User on 04.08.2025.
//

#include <iostream>
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
    void Renderer_2D::drawLine(std::vector<uint32_t>& buffer, int w, int h, vec2& p1, vec2& p2, uint32_t color){

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
                buffer.at(y * w + x) = color;
//                window.DrawPixel(y, x, color);
            } else {
                buffer.at(y * w + x) = color;
            }

            error -= dy;
            if (error < 0) {
                y += ystep;
                error += dx;
            }
        }
    }

    void Renderer_2D::drawLine(std::vector<uint32_t>& buffer, int w, int h, int x0,int y0, int x1, int y1, uint32_t color){

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
                drawPixelToBuffer(buffer,w,h,x,y,color);
//                window.DrawPixel(y, x, color);
            } else {
                drawPixelToBuffer(buffer,w,h,x,y,color);
            }

            error -= dy;
            if (error < 0) {
                y += ystep;
                error += dx;
            }
        }
    }

    void Renderer_2D::drawTriangleWireFrame(std::vector<uint32_t>& buffer, int w, int h, vec3& v0, vec3& v1, vec3& v2, uint32_t color){
        drawLine(buffer,w,h,static_cast<int>(v0.x), static_cast<int>(v0.y),
                 static_cast<int>(v1.x), static_cast<int>(v1.y), color);

        drawLine(buffer,w,h,static_cast<int>(v1.x), static_cast<int>(v1.y),
                 static_cast<int>(v2.x), static_cast<int>(v2.y), color);

        drawLine(buffer,w,h,static_cast<int>(v2.x), static_cast<int>(v2.y),
                 static_cast<int>(v0.x), static_cast<int>(v0.y), color);
    }

    void Renderer_2D::drawPixelToBuffer(std::vector<uint32_t> &buffer, int w, int h, int x, int y, uint32_t color) {
        if (x < 0 || x >= w || y < 0 || y >= h) {
            //std::cout << "Renderer: ERROR: Tried to draw out of bounds pixel \n";
            return;
        }
        buffer.at(y * w + x) = color;
    }
}