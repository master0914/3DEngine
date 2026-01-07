//
// Created by augus on 26.09.2025.
//
#include "../header/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb_image.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


namespace Engine {
    Image::Image(int width, int height, uint32_t fillColor)
        : m_Width(width), m_Height(height)
    {
        if(width <= 0 || height <= 0)
            throw std::invalid_argument("Image dimensions must be positive");

        m_Pixels.resize(width * height, fillColor);
    }

    Image::Image(const std::string& filepath) {
        std::string absolute_path;
        if(filepath.find(":") == std::string::npos) {
            // Relativer Pfad - mache absolut
            absolute_path = "C:/Users/augus/CLionProjects/3DEngine/" + filepath;
        } else {
            absolute_path = filepath;  // Schon absolut
        }

        // std::cout << "Loading: " << absolute_path << std::endl;

        if(!loadPNG(filepath)) {
            throw std::runtime_error("Failed to load PNG: " + filepath);
        }
    }

    bool Image::loadPNG(const std::string& filepath) {
        int width, height, channels;

        // Bild laden mit 4 Kanälen (RGBA)
        unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if(!data) {
            std::cerr << "STB Image Error: " << stbi_failure_reason() << std::endl;
            return false;
        }

        m_Width = width;
        m_Height = height;
        m_Pixels.resize(m_Width * m_Height);

        // Konvertiere zu 32-bit ARGB (wie dein Renderer es erwartet)
        for(int y = 0; y < m_Height; y++) {
            for(int x = 0; x < m_Width; x++) {
                int index = (y * m_Width + x);
                unsigned char* pixel = data + (index * 4); // 4 bytes per pixel (RGBA)

                // RGBA zu ARGB konvertieren
                uint32_t argb = (pixel[3] << 24) |  // Alpha
                               (pixel[0] << 16) |  // Rot
                               (pixel[1] << 8) |   // Grün
                               (pixel[2]);         // Blau

                m_Pixels[index] = argb;
            }
        }

        stbi_image_free(data);
        // std::cout << "Loaded image: " << filepath << " (" << m_Width << "x" << m_Height << ")" << std::endl;
        return true;
    }

    uint32_t Image::getPixel(int x, int y) const {
        if(!isValidCoord(x, y)) return 0;
        return m_Pixels[y * m_Width + x];
    }

    void Image::setPixel(int x, int y, uint32_t color) {
        if(isValidCoord(x, y)) {
            m_Pixels[y * m_Width + x] = color;
        }
    }

    void Image::fill(uint32_t color) {
        std::fill(m_Pixels.begin(), m_Pixels.end(), color);
    }

    bool Image::isValidCoord(int x, int y) const {
        return x >= 0 && x < m_Width && y >= 0 && y < m_Height;
    }
}
