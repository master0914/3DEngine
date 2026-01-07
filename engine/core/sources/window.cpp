//
// Created by augus on 07.01.2026.
//
#include "window.h"
#include <SDL2/SDL.h>
#include <cstring>
#include <iostream>

namespace Engine {

    // SDL-spezifische Daten
    struct Window::PlatformData {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;
    };

    // ---------------- Konstruktor ----------------
    Window::Window(int width, int height, const char* title)
        : m_Width(width), m_Height(height)
    {
        // Pixelbuffer initialisieren
        m_PixelBuffer = new uint32_t[width * height];
        std::memset(m_PixelBuffer, 0, width * height * sizeof(uint32_t));

        m_Data = new PlatformData();

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
            return;
        }

        m_Data->window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            0
        );

        m_Data->renderer = SDL_CreateRenderer(
            m_Data->window,
            -1,
            SDL_RENDERER_ACCELERATED
        );

        m_Data->texture = SDL_CreateTexture(
            m_Data->renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            width, height
        );
    }

    // ---------------- Destruktor ----------------
    Window::~Window() {
        if (m_Data) {
            if (m_Data->texture) SDL_DestroyTexture(m_Data->texture);
            if (m_Data->renderer) SDL_DestroyRenderer(m_Data->renderer);
            if (m_Data->window) SDL_DestroyWindow(m_Data->window);
            SDL_Quit();
            delete m_Data;
        }
        delete[] m_PixelBuffer;
    }

    // ---------------- Event-Polling ----------------
    void Window::PollEvents() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    m_ShouldClose = true;
                    break;

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    if (m_keyCallback)
                        m_keyCallback(e.key.keysym.sym, e.type == SDL_KEYDOWN);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    if (m_mouseButtonCallback)
                        m_mouseButtonCallback(
                            e.button.button,
                            e.type == SDL_MOUSEBUTTONDOWN
                        );
                    break;

                case SDL_MOUSEMOTION:
                    m_mouseX = e.motion.x;
                    m_mouseY = e.motion.y;
                    if (m_mouseMoveCallback)
                        m_mouseMoveCallback(m_mouseX, m_mouseY);
                    break;

                case SDL_MOUSEWHEEL:
                    if (m_scrollCallback)
                        m_scrollCallback(
                            static_cast<double>(e.wheel.x),
                            static_cast<double>(e.wheel.y)
                        );
                    break;
            }
        }
    }

    // ---------------- Rendering ----------------
    void Window::Clear() {
        std::memset(m_PixelBuffer, 0, m_Width * m_Height * sizeof(uint32_t));
    }

    void Window::Present() {
        SDL_UpdateTexture(
            m_Data->texture,
            nullptr,
            m_PixelBuffer,
            m_Width * sizeof(uint32_t)
        );
        SDL_RenderClear(m_Data->renderer);
        SDL_RenderCopy(m_Data->renderer, m_Data->texture, nullptr, nullptr);
        SDL_RenderPresent(m_Data->renderer);
    }

    void Window::swapBuffers(const std::vector<uint32_t>& newBuffer) {
        if (newBuffer.size() != static_cast<size_t>(m_Width * m_Height)) {
            std::cerr << "Window: Buffer size mismatch!" << std::endl;
            return;
        }
        std::memcpy(m_PixelBuffer, newBuffer.data(), newBuffer.size() * sizeof(uint32_t));
    }

    void Window::DrawPixel(int x, int y, uint32_t color) {
        if (x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
            m_PixelBuffer[y * m_Width + x] = color;
        }
    }

    void Window::DrawPixel(vec2& vec, uint32_t color) {
        DrawPixel(vec.getX(), vec.getY(), color);
    }

    void Window::DrawPixelArray(std::vector<uint32_t> buffer) {
        if (buffer.size() != static_cast<size_t>(m_Width * m_Height)) {
            std::cerr << "Window: Tried to draw buffer with differing dimension to window!" << std::endl;
            return;
        }
        std::memcpy(m_PixelBuffer, buffer.data(), buffer.size() * sizeof(uint32_t));
    }

    // ---------------- Callback Setter / Getter ----------------
    void Window::setKeyCallback(KeyCallback callback) { m_keyCallback = std::move(callback); }
    void Window::setMouseButtonCallback(MouseButtonCallback callback) { m_mouseButtonCallback = std::move(callback); }
    void Window::setMouseMoveCallback(MouseMoveCallback callback) { m_mouseMoveCallback = std::move(callback); }
    void Window::setScrollCallback(ScrollCallback callback) { m_scrollCallback = std::move(callback); }

    Window::KeyCallback Window::getKeyCallback() { return m_keyCallback; }
    Window::MouseButtonCallback Window::getMouseButtonCallback() { return m_mouseButtonCallback; }
    Window::MouseMoveCallback Window::getMouseMoveCallback() { return m_mouseMoveCallback; }
    Window::ScrollCallback Window::getScrollCallback() { return m_scrollCallback; }

}