//
// Created by User on 04.08.2025.
//

#ifndef RENDERER_2D_H
#define RENDERER_2D_H
#include <cstdint>

#include "image.h"
#include "window.h"
#include "../../Math/Vectors/VectorUtil.h"

#endif //RENDERER_2D_H
#pragma once

namespace Engine {
    class Renderer_2D {

    public:
        Renderer_2D(Window& window);

        // Buffer Management
        void beginFrame();
        void present();

        inline void drawPixel(int x, int y, uint32_t color) {
            if (!isValidCoord(x,y)) return;
            m_FrameBufferBack[y * m_Width + x] = color;
        }
        void drawRectangle(vec2& origin, int height, int width, uint32_t color);
        void fillRectangle(vec2& origin, int height, int width, uint32_t color);
        void drawRectangle(int x, int y, int height, int width, uint32_t color);
        void fillRectangle(int x, int y, int height, int width, uint32_t color);
        void drawCircle(vec2& middle, int radius, uint32_t color);
        void fillCircle(vec2& middle, int radius, uint32_t color);
        void drawTriangle(vec2& p1, vec2& p2, vec2& p3, uint32_t color);
        void drawLine(vec2& p1, vec2& p2, uint32_t color);
        void drawTileFromImage(int imgID, int x, int y, int tileX, int tileY, int tileSize);

        int loadImage(const std::string& filepath);
        void drawImage(int imgID, int x, int y);

        // void drawLine(std::vector<uint32_t>& buffer, int w, int h, vec2& p1, vec2& p2, uint32_t color);
        // void drawLine(std::vector<uint32_t>& buffer, int w, int h, int x1,int y1, int x2, int y2, uint32_t color);
        // void drawTriangleWireFrame(std::vector<uint32_t>& buffer, int w, int h, vec3& p1, vec3& p2, vec3& p3, uint32_t color);
        // void drawPixelToBuffer(std::vector<uint32_t>& buffer, int w, int h, int x, int y, uint32_t color);
    private:
        Window* m_Window;
        int m_Width, m_Height;

        // Double-Buffering wie in Renderer_3D
        std::vector<uint32_t> m_FrameBufferBack;
        std::vector<uint32_t> m_FrameBufferFront;

        // Image-Loading Cache
        std::vector<Image> m_LoadedImages;

        void clearBuffer(uint32_t color = 0xFF000000);
        bool isValidCoord(int x, int y) const;

        static bool isTransparent(uint32_t pixel) {
            // Check 1: Alpha = 0 (voll transparent)
            if(((pixel >> 24) & 0xFF) == 0) return true;

            // Check 2: Spezielle Transparent-Farbe (Magenta/Lila)
            if(pixel == 0xFFFF00FF) return true;

            return false;
        }
    };
}