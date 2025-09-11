//
// Created by Master0914 on 03.08.2025.
//
#include "../Header/window.h"
#include "../../math/Vectors/VectorUtil.h"

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#include <iostream>
#include <cstring>
#include "../../math/Vectors/VectorUtil.h"


namespace Engine {
    struct Window::PlatformData {
        HWND hwnd;
        HDC hdc;
        BITMAPINFO bmi;
    };

    // Forward-Deklaration der WindowProc
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    Window::Window(int width, int height, const char* title)
            : m_Width(width), m_Height(height) {
        // Pixelbuffer anlegen
        m_PixelBuffer = new uint32_t[width * height];
        m_Data = new PlatformData;

        // Windows-Initialisierung
        HINSTANCE hInstance = GetModuleHandle(nullptr);

        // Fensterklasse registrieren
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = "EngineWindow";
        RegisterClass(&wc);

        // Fenster erstellen
        m_Data->hwnd = CreateWindow(
                "EngineWindow", title,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT,
                width, height,
                nullptr, nullptr, hInstance, nullptr);

        // Device Context holen
        m_Data->hdc = GetDC(m_Data->hwnd);

        // BITMAPINFO für Present()
        ZeroMemory(&m_Data->bmi, sizeof(BITMAPINFO));
        m_Data->bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        m_Data->bmi.bmiHeader.biWidth = width;
        m_Data->bmi.bmiHeader.biHeight = -height; // Top-down
        m_Data->bmi.bmiHeader.biPlanes = 1;
        m_Data->bmi.bmiHeader.biBitCount = 32;
        m_Data->bmi.bmiHeader.biCompression = BI_RGB;

        // Fenster anzeigen
        ShowWindow(m_Data->hwnd, SW_SHOW);

        // Window-Pointer speichern
        SetWindowLongPtr(m_Data->hwnd, GWLP_USERDATA, (LONG_PTR)this);
    }

    Window::~Window() {
        if (m_Data) {
            ReleaseDC(m_Data->hwnd, m_Data->hdc);
            DestroyWindow(m_Data->hwnd);
            delete m_Data;
        }
        delete[] m_PixelBuffer;
    }

    void Window::PollEvents() {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Window::Clear() {
        memset(m_PixelBuffer, 0, m_Width * m_Height * sizeof(uint32_t));
    }

    void Window::Present() {
        StretchDIBits(
                m_Data->hdc,
                0, 0, m_Width, m_Height, // Ziel
                0, 0, m_Width, m_Height, // Quelle
                m_PixelBuffer,
                &m_Data->bmi,
                DIB_RGB_COLORS,
                SRCCOPY
        );
    }

    void Window::DrawPixel(int x, int y, uint32_t color) {
        if (x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
            m_PixelBuffer[y * m_Width + x] = color;
        }
    }
    void Window::DrawPixel(vec2& vec, uint32_t color) {
        int x = vec.getX();
        int y = vec.getY();
        if (x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
            m_PixelBuffer[y * m_Width + x] = color;
        }
    }

    void Window::DrawPixelArray(std::vector<uint32_t> buffer) {
        if(buffer.size() != m_Width * m_Height) {
            std::cerr << "Window: ERROR: Tried to draw buffer with differing dimension to window! "
                      << "Expected: " << (m_Width * m_Height) << " pixels, "
                      << "Got: " << buffer.size() << " pixels." << std::endl;
            return;
        }
        std::memcpy(m_PixelBuffer, buffer.data(), buffer.size() * sizeof(uint32_t));
    }

    // Message-Handler
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if(!window){
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        switch (msg) {
            case WM_CLOSE:
                window->SetShouldClose(true);
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            case WM_KEYDOWN:
            case WM_KEYUP: {
                if (window->m_keyCallback()) {
                    int action = (msg == WM_KEYDOWN) ? 1 : 0;
                    window->getKeyCallback()(static_cast<int>(wParam), action);
                }
                break;
            }

            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP: {
                if (window->m_mouseButtonCallback()) {
                    int button = 0;
                    int action = 0;

                    if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) {
                        button = 0; // Left button
                        action = (msg == WM_LBUTTONDOWN) ? 1 : 0;
                    } else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                        button = 1; // Right button
                        action = (msg == WM_RBUTTONDOWN) ? 1 : 0;
                    } else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                        button = 2; // Middle button
                        action = (msg == WM_MBUTTONDOWN) ? 1 : 0;
                    }

                    window->m_mouseButtonCallback(button, action);
                }
                break;
            }

            case WM_MOUSEMOVE: {
                if (window->m_mouseMoveCallback) {
                    double x = static_cast<double>(GET_X_LPARAM(lParam));
                    double y = static_cast<double>(GET_Y_LPARAM(lParam));
                    window->m_mouseX = x;
                    window->m_mouseY = y;
                    window->m_mouseMoveCallback(x, y);
                }
                break;
            }

            case WM_MOUSEWHEEL: {
                if (window->m_scrollCallback) {
                    double delta = static_cast<double>(GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA;
                    window->m_scrollCallback(0.0, delta);
                }
                break;
            }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    // callback setter
    void Window::setKeyCallback(KeyCallback callback) {
        m_keyCallback = std::move(callback);
    }

    void Window::setMouseButtonCallback(MouseButtonCallback callback) {
        m_mouseButtonCallback = std::move(callback);
    }

    void Window::setMouseMoveCallback(MouseMoveCallback callback) {
        m_mouseMoveCallback = std::move(callback);
    }

    void Window::setScrollCallback(ScrollCallback callback) {
        m_scrollCallback = std::move(callback);
    }

    Window::KeyCallback Window::getKeyCallback() {
        return m_keyCallback;
    }

    Window::MouseButtonCallback Window::getMouseButtonCallback() {
        return m_mouseButtonCallback;
    }

    Window::MouseMoveCallback Window::getMouseMoveCallback() {
        return m_mouseMoveCallback;
    }

    Window::ScrollCallback Window::getScrollCallback() {
        return m_scrollCallback;
    }
}
#else
// Platzhalter für andere Plattformen
namespace Engine {
    Window::Window(int, int, const char*) {}
    Window::~Window() {}
    void Window::PollEvents() {}
    void Window::Clear() {}
    void Window::Present() {}
    void Window::DrawPixel(int, int, uint32_t) {}
}
#endif

