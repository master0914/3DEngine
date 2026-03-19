//
// Created by Master0914 on 03.08.2025.
//

#ifndef INC_3DENGINE_WINDOW_H
#define INC_3DENGINE_WINDOW_H
#include "vector.h"

#endif //INC_3DENGINE_WINDOW_H

#pragma once
#include <string>

#include <vector>
#include <cstdint>
#include <functional>
// #include "../../math/Vectors/VectorUtil.h"


namespace Engine{
    class Window{
    public:
        using KeyCallback = std::function<void(int key, int action)>;
        using MouseButtonCallback = std::function<void(int button, int action)>;
        using MouseMoveCallback = std::function<void(double x, double y)>;
        using ScrollCallback = std::function<void(double xoffset, double yoffset)>;
        using TextInputCallback = std::function<void(const char*)>;

        Window(int width, int height, const char* title);
        ~Window();

        // eventDispatcher
        void PollEvents() ;
        [[nodiscard]] bool ShouldClose() const  { return m_ShouldClose; }

        // callback methoden
        void setKeyCallback(KeyCallback callback);
        void setMouseButtonCallback(MouseButtonCallback callback);
        void setMouseMoveCallback(MouseMoveCallback callback);
        void setScrollCallback(ScrollCallback callback);
        void setTextInputCallback(TextInputCallback callback);

        [[nodiscard]] KeyCallback getKeyCallback() const;
        [[nodiscard]] MouseButtonCallback getMouseButtonCallback() const;
        [[nodiscard]] MouseMoveCallback getMouseMoveCallback() const;
        [[nodiscard]] ScrollCallback getScrollCallback() const;
        [[nodiscard]] TextInputCallback getTextInputCallback() const;


        // renderer
        void Clear() ;
        void Present() ;
        void DrawPixel(int x, int y, uint32_t color) ;
        void DrawPixel(vec2& vec, uint32_t color) ;
        void DrawPixelArray(std::vector<uint32_t> buffer);

        // pixelbuffer zugriff
        [[nodiscard]] const uint32_t* getPixelBuffer() const { return m_PixelBuffer; }
        [[nodiscard]] int getBufferSize() const { return m_Width * m_Height; }

        void swapBuffers(const std::vector<uint32_t>& newBuffer);

        [[nodiscard]] int getm_Height() const{return m_Height;}
        [[nodiscard]] int getm_Width() const{return m_Width;}

        // Für WindowProc-Zugriff
        void SetShouldClose(bool shouldClose) { m_ShouldClose = shouldClose; }

        // callback speicher
        KeyCallback m_keyCallback;
        MouseButtonCallback m_mouseButtonCallback;
        MouseMoveCallback m_mouseMoveCallback;
        ScrollCallback m_scrollCallback;
        TextInputCallback m_textInputCallback;

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

    struct Framebuffer{

    };
}
