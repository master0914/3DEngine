//
// Created by Master0914 on 03.08.2025.
//

#ifndef INC_3DENGINE_WINDOW_H
#define INC_3DENGINE_WINDOW_H

#endif //INC_3DENGINE_WINDOW_H

#pragma once
#include <string>
#include <minwindef.h>
#include <windef.h>
#include <vector>
#include "../core/Header/Interfaces.h"


namespace Engine{
    class Window : public IEventDispatcher, public IRenderer {

    public:
        Window(int width, int height, const char* title);
        ~Window();

        // IEventDispatcher
        void PollEvents() override;
        bool ShouldClose() const override { return m_ShouldClose; }

        // IRenderer
        void Clear() override;
        void Present() override;
        void DrawPixel(int x, int y, uint32_t color) override;
        void DrawPixel(vec2& vec, uint32_t color) override;
        void DrawPixelArray(std::vector<uint32_t> buffer);

        // Pixelbuffer-Zugriff
        uint32_t* GetPixelBuffer() { return m_PixelBuffer; }
        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }

        // Für WindowProc-Zugriff
        void SetShouldClose(bool shouldClose) { m_ShouldClose = shouldClose; }

    private:
        bool m_ShouldClose = false;
        uint32_t* m_PixelBuffer;
        int m_Width, m_Height;
        struct PlatformData; // Forward Declaration
        PlatformData* m_Data;
    };
}
