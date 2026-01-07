//
// Created by User on 04.08.2025.
//

#include <iostream>
#include "../header/renderer_2D.h"

#include "bitmapFont.h"
#include "../../../../../src/util/Logger.h"

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

        loadDefaultFont();
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
        drawRectangle(origin.getX(),origin.getY() , height, width, color);
    }
    void Renderer_2D::fillRectangle(vec2& origin, int height, int width, uint32_t color) {
        fillRectangle(origin.getX(),origin.getY() , height, width, color);
    }

    void Renderer_2D::drawRectangle(int x, int y, int height, int width, uint32_t color) {
        for(int dx = 0; dx < width; dx++) {
            drawPixel(x + dx, y, color);
        }
        for(int dx = 0; dx < width; dx++) {
            drawPixel(x + dx, y + height - 1, color);
        }
        for(int dy = 0; dy < height; dy++) {
            drawPixel(x, y + dy, color);
        }
        for(int dy = 0; dy < height; dy++) {
            drawPixel(x + width - 1, y + dy, color);
        }
    }
    void Renderer_2D::fillRectangle(int x, int y, int height, int width, uint32_t color) {
        for(int dy = 0; dy < height; dy++) {
            for(int dx = 0; dx < width; dx++) {
                int pixelX = x + dx;
                int pixelY = y + dy;

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

    void Renderer_2D::loadDefaultFont() {


        // Font initialisieren: 8x8 Pixel, 16 Zeichen pro Zeile, 128 Bytes breit (16*8)
        m_font = new BitmapFont(SIMPLE_FONT,7,8);
    }
    void Renderer_2D::drawText(const std::string& text, int x, int y, uint32_t color) {
        if (!m_font) {LOG_ERROR("No bitmapFont found!!!");return;}
        m_font->drawText(m_FrameBufferBack, m_Width, m_Height, text, x, y, color);
    }
    void Renderer_2D::drawText(const std::string& text, const vec2& position, uint32_t color) {
        drawText(text, static_cast<int>(position.getX()), static_cast<int>(position.getY()), color);
    }
}









