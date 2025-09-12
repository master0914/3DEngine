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
#include <cstdint>
#include <functional>
#include "../../math/Vectors/VectorUtil.h"


namespace Engine{
    class Window{
    public:
        using KeyCallback = std::function<void(int key, int action)>;
        using MouseButtonCallback = std::function<void(int button, int action)>;
        using MouseMoveCallback = std::function<void(double x, double y)>;
        using ScrollCallback = std::function<void(double xoffset, double yoffset)>;

        Window(int width, int height, const char* title);
        ~Window();

        // eventDispatcher
        void PollEvents() ;
        bool ShouldClose() const  { return m_ShouldClose; }

        // callback methoden
        void setKeyCallback(KeyCallback callback);
        void setMouseButtonCallback(MouseButtonCallback callback);
        void setMouseMoveCallback(MouseMoveCallback callback);
        void setScrollCallback(ScrollCallback callback);

        KeyCallback getKeyCallback();
        MouseButtonCallback getMouseButtonCallback();
        MouseMoveCallback getMouseMoveCallback();
        ScrollCallback getScrollCallback();


        // renderer
        void Clear() ;
        void Present() ;
        void DrawPixel(int x, int y, uint32_t color) ;
        void DrawPixel(vec2& vec, uint32_t color) ;
        void DrawPixelArray(std::vector<uint32_t> buffer);

        // pixelbuffer zugriff
        uint32_t* GetPixelBuffer() { return m_PixelBuffer; }
        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }

        // Für WindowProc-Zugriff
        void SetShouldClose(bool shouldClose) { m_ShouldClose = shouldClose; }

        // callback speicher
        KeyCallback m_keyCallback;
        MouseButtonCallback m_mouseButtonCallback;
        MouseMoveCallback m_mouseMoveCallback;
        ScrollCallback m_scrollCallback;

        double m_mouseX = 0.0;
        double m_mouseY = 0.0;
    private:


        // input daten

        bool m_ShouldClose = false;

        // pixelbuffer
        uint32_t* m_PixelBuffer;
        int m_Width, m_Height;

        struct PlatformData; // forward declaration
        PlatformData* m_Data;
    };
}
