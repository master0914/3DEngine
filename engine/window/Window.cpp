//
// Created by Master0914 on 03.08.2025.
//
#include "Window.h"

#include <cstdint>

#ifdef _WIN32
#include <windows.h>


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

    // Message-Handler
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        switch (msg) {
            case WM_CLOSE:
                if (window) window->SetShouldClose(true);
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
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

