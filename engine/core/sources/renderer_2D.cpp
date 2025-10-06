//
// Created by User on 04.08.2025.
//

#include <iostream>
#include "../Header/renderer_2D.h"

namespace Engine {
    // TODO: Rework without window.drawPiexl
    Renderer_2D::Renderer_2D(Window& window) {
        m_Window = &window;
        m_Width = window.getm_Width();
        m_Height = window.getm_Height();

        // Buffer initialisieren wie in Renderer_3D
        m_FrameBufferBack.resize(m_Width * m_Height);
        m_FrameBufferFront.resize(m_Width * m_Height);

        clearBuffer(0xFF000000);
    }

    void Renderer_2D::beginFrame() {
        clearBuffer(0xFF000000);
    }

    void Renderer_2D::present() {
        // Buffer swap wie in Renderer_3D
        std::swap(m_FrameBufferFront, m_FrameBufferBack);
        m_Window->swapBuffers(m_FrameBufferFront);
        m_Window->Present();
    }

    void Renderer_2D::clearBuffer(uint32_t color) {
        std::fill(m_FrameBufferBack.begin(), m_FrameBufferBack.end(), color);
    }

    int Renderer_2D::loadImage(const std::string& filepath) {
        try {
            m_LoadedImages.emplace_back(filepath); // Deine Image-Klasse mit PNG Support
            return m_LoadedImages.size() - 1; // Rückgabe Image-ID
        }
        catch(const std::exception& e) {
            std::cerr << "Failed to load image: " << filepath << " - " << e.what() << std::endl;
            return -1;
        }
    }


    void Renderer_2D::drawRectangle(vec2& origin, int height, int width, uint32_t color) {
        // Obere Kante
        for(int dx = 0; dx < width; dx++) {
            drawPixel(origin.getX() + dx, origin.getY(), color);
        }
        // Untere Kante
        for(int dx = 0; dx < width; dx++) {
            drawPixel(origin.getX() + dx, origin.getY() + height - 1, color);
        }
        // Linke Kante
        for(int dy = 0; dy < height; dy++) {
            drawPixel(origin.getX(), origin.getY() + dy, color);
        }
        // Rechte Kante
        for(int dy = 0; dy < height; dy++) {
            drawPixel(origin.getX() + width - 1, origin.getY() + dy, color);
        }
    }
    void Renderer_2D::fillRectangle(vec2& origin, int height, int width, uint32_t color) {
        for(int dy = 0; dy < height; dy++) {
            for(int dx = 0; dx < width; dx++) {
                int pixelX = origin.getX() + dx;
                int pixelY = origin.getY() + dy;

                if(isValidCoord(pixelX, pixelY)) {
                    m_FrameBufferBack[pixelY * m_Width + pixelX] = color;
                }
            }
        }
    }
    void Renderer_2D::drawCircle(vec2& middle, int radius, uint32_t color){}
    void Renderer_2D::fillCircle(vec2& middle, int radius, uint32_t color){}
    void Renderer_2D::drawTriangle(vec2& p1, vec2& p2, vec2& p3, uint32_t color) {
        std::cout << "drawing triangle: \n" << p1 << p2 << p3 << "\n";
        drawLine(p1,p2,color);
        drawLine(p2,p3,color);
        drawLine(p1,p3,color);
    }
    void Renderer_2D::drawLine(vec2& p1, vec2& p2, uint32_t color) {
        int x0 = static_cast<int>(p1.getX());
        int y0 = static_cast<int>(p1.getY());
        int x1 = static_cast<int>(p2.getX());
        int y1 = static_cast<int>(p2.getY());
        std::cout << "with coordinates: \n" << x0 << "  "<< y0 << "  "<< x1 << "  "<< y1 << "  ";
        // Sonderfall: Punkt
        if (x0 == x1 && y0 == y1) {
            drawPixel(x0, y0, color);
            drawPixel(1,1,3);
            return;
        }

        // Sonderfall: Vertikale Linie
        if (x0 == x1) {
            if (y0 > y1) std::swap(y0, y1);
            for (int y = y0; y <= y1; y++) {
                drawPixel(x0, y, color);
            }
            return;
        }

        // Sonderfall: Horizontale Linie
        if (y0 == y1) {
            if (x0 > x1) std::swap(x0, x1);
            for (int x = x0; x <= x1; x++) {
                drawPixel(x, y0, color);
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
            drawPixel(x0, y0, color);
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

    void Renderer_2D::drawImage(int imgID, int x, int y) {
        Image img = m_LoadedImages[imgID];
        int height = img.getHeight();
        int width = img.getWidth();
        for(int dy = 0; dy < height; dy++) {
            for(int dx = 0; dx < width; dx++) {
                // Texture coordinates
                float u = (float)dx / width;
                float v = (float)dy / height;

                int srcX = u * width;
                int srcY = v * height;

                uint32_t pixel = img.getPixel(srcX, srcY);

                // Alpha Check (nur zeichnen wenn nicht transparent)
                if(!isTransparent(pixel) ) {
                    int destX = x + dx;
                    int destY = y + dy;

                    if(isValidCoord(destX, destY)) {
                        m_FrameBufferBack[destY * m_Width + destX] = pixel;
                    }
                }
            }
        }
    }
    void Renderer_2D::drawTileFromImage(int imgID, int x, int y, int tileX, int tileY, int tileSize) {
        // lässt dich quadratische ausschnitte eines bildes rendern
        Image img = m_LoadedImages[imgID];

        int srcStartX = tileX * tileSize;
        int srcStartY = tileY * tileSize;

        for(int dy = 0; dy < tileSize; dy++) {
            for(int dx = 0; dx < tileSize; dx++) {
                int srcX = srcStartX + dx;
                int srcY = srcStartY + dy;

                uint32_t pixel = img.getPixel(srcX, srcY);

                // Alpha Check (nur zeichnen wenn nicht transparent)
                if(!isTransparent(pixel) ) {
                    int destX = x + dx;
                    int destY = y + dy;

                    if(isValidCoord(destX, destY)) {
                        m_FrameBufferBack[destY * m_Width + destX] = pixel;
                    }
                }
            }
        }

    }


    bool Renderer_2D::isValidCoord(int x, int y) const {
        return x >= 0 && x < m_Width && y >= 0 && y < m_Height;
    }
}







//     void Renderer_2D::drawLine(std::vector<uint32_t>& buffer, int w, int h, vec2& p1, vec2& p2, uint32_t color){
//
//         int x0 = static_cast<int>(p1.getX());
//         int y0 = static_cast<int>(p1.getY());
//         int x1 = static_cast<int>(p2.getX());
//         int y1 = static_cast<int>(p2.getY());
//         // Sonderfall: Punkt
//         if (x0 == x1 && y0 == y1) {
//             drawPixelToBuffer(buffer, w, h, x0, y0, color);
//             return;
//         }
//
//         // Sonderfall: Vertikale Linie
//         if (x0 == x1) {
//             if (y0 > y1) std::swap(y0, y1);
//             for (int y = y0; y <= y1; y++) {
//                 drawPixelToBuffer(buffer, w, h, x0, y, color);
//             }
//             return;
//         }
//
//         // Sonderfall: Horizontale Linie
//         if (y0 == y1) {
//             if (x0 > x1) std::swap(x0, x1);
//             for (int x = x0; x <= x1; x++) {
//                 drawPixelToBuffer(buffer, w, h, x, y0, color);
//             }
//             return;
//         }
//
//         // Normale diagonale Linie - Bresenham Algorithmus
//         int dx = std::abs(x1 - x0);
//         int dy = std::abs(y1 - y0);
//         int sx = (x0 < x1) ? 1 : -1;
//         int sy = (y0 < y1) ? 1 : -1;
//         int err = dx - dy;
//
//         while (true) {
//             drawPixelToBuffer(buffer, w, h, x0, y0, color);
//             if (x0 == x1 && y0 == y1) break;
//
//             int e2 = 2 * err;
//             if (e2 > -dy) {
//                 err -= dy;
//                 x0 += sx;
//             }
//             if (e2 < dx) {
//                 err += dx;
//                 y0 += sy;
//             }
//         }
//     }
//     void Renderer_2D::drawLine(std::vector<uint32_t>& buffer, int w, int h, int x0,int y0, int x1, int y1, uint32_t color){
//
//         // Sonderfall: Punkt
//         if (x0 == x1 && y0 == y1) {
//             drawPixelToBuffer(buffer, w, h, x0, y0, color);
//             return;
//         }
//
//         // Sonderfall: Vertikale Linie
//         if (x0 == x1) {
//             if (y0 > y1) std::swap(y0, y1);
//             for (int y = y0; y <= y1; y++) {
//                 drawPixelToBuffer(buffer, w, h, x0, y, color);
//             }
//             return;
//         }
//
//         // Sonderfall: Horizontale Linie
//         if (y0 == y1) {
//             if (x0 > x1) std::swap(x0, x1);
//             for (int x = x0; x <= x1; x++) {
//                 drawPixelToBuffer(buffer, w, h, x, y0, color);
//             }
//             return;
//         }
//
//         // Normale diagonale Linie - Bresenham Algorithmus
//         int dx = std::abs(x1 - x0);
//         int dy = std::abs(y1 - y0);
//         int sx = (x0 < x1) ? 1 : -1;
//         int sy = (y0 < y1) ? 1 : -1;
//         int err = dx - dy;
//
//         while (true) {
//             drawPixelToBuffer(buffer, w, h, x0, y0, color);
//             if (x0 == x1 && y0 == y1) break;
//
//             int e2 = 2 * err;
//             if (e2 > -dy) {
//                 err -= dy;
//                 x0 += sx;
//             }
//             if (e2 < dx) {
//                 err += dx;
//                 y0 += sy;
//             }
//         }
//     }
//     void Renderer_2D::drawTriangleWireFrame(std::vector<uint32_t>& buffer, int w, int h, vec3& v0, vec3& v1, vec3& v2, uint32_t color){
// //        std::cout << "Line from (" << v0.x << "," << v0.y << ") to (" << v1.x << "," << v1.y << ")\n";
//         drawLine(buffer,w,h,static_cast<int>(v0.x), static_cast<int>(v0.y),
//                  static_cast<int>(v1.x), static_cast<int>(v1.y), color);
// //        std::cout << "Line from (" << v1.x << "," << v1.y << ") to (" << v2.x << "," << v2.y << ")\n";
//         drawLine(buffer,w,h,static_cast<int>(v1.x), static_cast<int>(v1.y),
//                  static_cast<int>(v2.x), static_cast<int>(v2.y), color);
// //        std::cout << "Line from (" << v2.x << "," << v2.y << ") to (" << v0.x << "," << v0.y << ")\n";
//         drawLine(buffer,w,h,static_cast<int>(v2.x), static_cast<int>(v2.y),
//                  static_cast<int>(v0.x), static_cast<int>(v0.y), color);
//     }
//     void Renderer_2D::drawPixelToBuffer(std::vector<uint32_t> &buffer, int w, int h, int x, int y, uint32_t color) {
// #ifdef DEBUG
//         if (x < 0 || x >= w || y < 0 || y >= h) {
//             std::cout << "Renderer: ERROR: Tried to draw out of bounds pixel \n";
//             return;
//         }
// #endif
//         buffer.at(y * w + x) = color;
//     }

