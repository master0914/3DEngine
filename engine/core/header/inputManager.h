//
// Created by Master0914 on 11.09.2025.
//

#ifndef INC_3DENGINE_INPUTMANAGER_H
#define INC_3DENGINE_INPUTMANAGER_H

#endif //INC_3DENGINE_INPUTMANAGER_H

#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include "../../math/Vectors/VectorUtil.h"
#include "window.h"

namespace Engine {

    enum class KeyCode {
        // Alphabet
        KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
        KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
        KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

        // Numbers
        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,

        // Function keys
        KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
        KEY_F9, KEY_F10, KEY_F11, KEY_F12,

        // Special keys
        KEY_SPACE, KEY_ENTER, KEY_ESCAPE, KEY_BACKSPACE, KEY_TAB, KEY_SHIFT,
        KEY_CTRL, KEY_ALT, KEY_CAPSLOCK, KEY_INSERT, KEY_DELETE, KEY_HOME,
        KEY_END, KEY_PAGEUP, KEY_PAGEDOWN,

        // Arrow keys
        KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,

        // Numpad
        KEY_NUMPAD_0, KEY_NUMPAD_1, KEY_NUMPAD_2, KEY_NUMPAD_3, KEY_NUMPAD_4,
        KEY_NUMPAD_5, KEY_NUMPAD_6, KEY_NUMPAD_7, KEY_NUMPAD_8, KEY_NUMPAD_9,

        // Mouse buttons
        MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE, MOUSE_BUTTON_4, MOUSE_BUTTON_5,

        // Count
        KEY_COUNT
    };

    enum class InputState {
        RELEASED = 0,
        PRESSED = 1,
        JUST_PRESSED = 2,
        JUST_RELEASED = 3
    };

    // Lookup-Array für KeyCode-Namen
    static constexpr std::array<const char*, static_cast<size_t>(KeyCode::KEY_COUNT)> KeyCodeNames = {
            // Alphabet
            "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
            "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
            "U", "V", "W", "X", "Y", "Z",

            // Numbers
            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",

            // Function keys
            "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
            "F9", "F10", "F11", "F12",

            // Special keys
            "SPACE", "ENTER", "ESCAPE", "BACKSPACE", "TAB", "SHIFT",
            "CTRL", "ALT", "CAPSLOCK", "INSERT", "DELETE", "HOME",
            "END", "PAGEUP", "PAGEDOWN",

            // Arrow keys
            "UP", "DOWN", "LEFT", "RIGHT",

            // Numpad
            "NUMPAD_0", "NUMPAD_1", "NUMPAD_2", "NUMPAD_3", "NUMPAD_4",
            "NUMPAD_5", "NUMPAD_6", "NUMPAD_7", "NUMPAD_8", "NUMPAD_9",

            // Mouse buttons
            "MOUSE_LEFT", "MOUSE_RIGHT", "MOUSE_MIDDLE", "MOUSE_BUTTON_4", "MOUSE_BUTTON_5"
    };

// Hilfsfunktion zum Konvertieren
    inline const char* keyCodeToString(KeyCode code) {
        size_t index = static_cast<size_t>(code);
        if (index < KeyCodeNames.size()) {
            return KeyCodeNames[index];
        }
        return "UNKNOWN";
    }

    class InputManager {
    public:
        InputManager();

        ~InputManager() = default;

        // Initialisierung mit Window
        void initialize(Window *window);

        // Update muss jeden Frame aufgerufen werden
        void update();

        // Key states
        bool isKeyPressed(KeyCode key) const;

        bool isKeyJustPressed(KeyCode key) const;

        bool isKeyJustReleased(KeyCode key) const;

        // Mouse states
        bool isMouseButtonPressed(KeyCode button) const;

        bool isMouseButtonJustPressed(KeyCode button) const;

        bool isMouseButtonJustReleased(KeyCode button) const;

        // Mouse position
        vec2 getMousePosition() const;

        vec2 getMouseDelta() const;

        float getMouseScroll() const;

        // Event callbacks
        void setKeyCallback(std::function<void(KeyCode, InputState)> callback);

        void setMouseCallback(std::function<void(KeyCode, InputState)> callback);

        void setScrollCallback(std::function<void(double)> callback);

        // Window callbacks (werden vom Window aufgerufen)
        void onKeyEvent(int key, int action);

        void onMouseButtonEvent(int button, int action);

        void onMouseMoveEvent(double x, double y);

        void onScrollEvent(double xoffset, double yoffset);

    private:
        void updateKeyStates();

    private:
        Window *m_window = nullptr;

        // Key states
        InputState m_keyStates[static_cast<int>(KeyCode::KEY_COUNT)];
        InputState m_prevKeyStates[static_cast<int>(KeyCode::KEY_COUNT)];

        // Mouse
        vec2 m_mousePosition;
        vec2 m_prevMousePosition;
        vec2 m_mouseDelta;
        float m_scrollDelta;

        // Callbacks
        std::function<void(KeyCode, InputState)> m_keyCallback;
        std::function<void(KeyCode, InputState)> m_mouseCallback;
        std::function<void(double)> m_scrollCallback;

        // Key mapping (kann je nach Backend angepasst werden)
        std::unordered_map<int, KeyCode> m_keyMap;
        std::unordered_map<int, KeyCode> m_mouseMap;

        void setupKeyMappings();
    };
}