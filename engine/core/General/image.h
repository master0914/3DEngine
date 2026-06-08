//
// Created by augus on 26.09.2025.
//

#ifndef INC_3DENGINE_IMAGE_H
#define INC_3DENGINE_IMAGE_H
#pragma once
#include <cstdint>
#include <string>
#include <vector>

#endif //INC_3DENGINE_IMAGE_H

namespace Engine {
    class Image {
    public:
        Image(): m_Width(0),m_Height(0){}
        explicit Image(const std::string& filepath);
        Image(int width, int height, uint32_t color = 0x00000000);
        Image(int width, int height, std::vector<uint32_t> imageData); // actually copys no big overhead

        uint32_t getPixel(int x, int y) const;
        void setPixel(int x, int y, uint32_t color);
        void fill(uint32_t color);

        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }
        const uint32_t* getData() const { return m_Pixels.data(); }

        bool isValidCoord(int x, int y) const;
        void clear(){fill(0x00000000);}

        Image(const Image&) = default;
        Image(Image&&) = default;
        Image& operator=(const Image&) = default;
        Image& operator=(Image&&) = default;
    private:
        bool loadPNG(const std::string& filepath);

        int m_Width, m_Height;
        std::vector<uint32_t> m_Pixels;
    };
}