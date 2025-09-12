//
// Created by Master0914 on 11.09.2025.
//
#include <iostream>
#include <windows.h>
#include "../header/inputManager.h"

namespace Engine{
    InputManager::InputManager() {
        for(int i = 0; i < static_cast<int>(KeyCode::KEY_COUNT);++i){
            m_keyStates[i] = InputState::RELEASED;
            m_prevKeyStates[i] = InputState::RELEASED;
        }
    }

    void InputManager::initialize(Engine::Window *window) {
        m_window = window;
        if (m_window) {
            m_window->setKeyCallback([this](int key, int action) {
                this->onKeyEvent(key, action);
            });

            m_window->setMouseButtonCallback([this](int button, int action) {
                this->onMouseButtonEvent(button, action);
            });

            m_window->setMouseMoveCallback([this](double x, double y) {
                this->onMouseMoveEvent(x, y);
            });

            m_window->setScrollCallback([this](double xoffset, double yoffset) {
                this->onScrollEvent(xoffset, yoffset);
            });
        }
    }

    void InputManager::update() {
        // Speichere previous states
        for (int i = 0; i < static_cast<int>(KeyCode::KEY_COUNT); ++i) {
            m_prevKeyStates[i] = m_keyStates[i];
        }

        // Update key states
        updateKeyStates();

        // Reset mouse delta und scroll
        m_mouseDelta = vec2(0.0f, 0.0f);
        m_scrollDelta = 0.0f;

        m_prevMousePosition = m_mousePosition;
    }

    void InputManager::updateKeyStates() {
        for (int i = 0; i < static_cast<int>(KeyCode::KEY_COUNT); ++i) {
            // Update state transitions
            if (m_keyStates[i] == InputState::JUST_PRESSED) {
                m_keyStates[i] = InputState::PRESSED;
            } else if (m_keyStates[i] == InputState::JUST_RELEASED) {
                m_keyStates[i] = InputState::RELEASED;
            }
        }
    }

//-------------------------------------------------------------------------------
    // Key states
    bool InputManager::isKeyPressed(KeyCode key) const {
        int index = static_cast<int>(key);
        return m_keyStates[index] == InputState::PRESSED ||
               m_keyStates[index] == InputState::JUST_PRESSED;
    }

    bool InputManager::isKeyJustPressed(KeyCode key) const {
        int index = static_cast<int>(key);
        return m_keyStates[index] == InputState::JUST_PRESSED;
    }

    bool InputManager::isKeyJustReleased(KeyCode key) const {
        int index = static_cast<int>(key);
        return m_keyStates[index] == InputState::JUST_RELEASED;
    }

    // Mouse states (same as key states)
    bool InputManager::isMouseButtonPressed(KeyCode button) const {
        return isKeyPressed(button);
    }

    bool InputManager::isMouseButtonJustPressed(KeyCode button) const {
        return isKeyJustPressed(button);
    }

    bool InputManager::isMouseButtonJustReleased(KeyCode button) const {
        return isKeyJustReleased(button);
    }

    // Mouse position
    vec2 InputManager::getMousePosition() const {
        return m_mousePosition;
    }

    vec2 InputManager::getMouseDelta() const {
        return m_mouseDelta;
    }

    float InputManager::getMouseScroll() const {
        return m_scrollDelta;
    }
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
    // Key callbacks
    // werden benutzt um extern eine funktion zu übergeben welche die inputs handelt
    // bsp von deepseek:
//      m_context.input->setKeyCallback([this](KeyCode key, InputState state) {
//          if (key == KeyCode::KEY_SPACE && state == InputState::JUST_PRESSED) {
//              hier kann man dann seinen code reinschreiben
//              this->jump();
//          }
//      });
    void InputManager::setKeyCallback(std::function<void(KeyCode, InputState)> callback) {
        m_keyCallback = std::move(callback);
    }

    void InputManager::setMouseCallback(std::function<void(KeyCode, InputState)> callback) {
        m_mouseCallback = std::move(callback);
    }

    void InputManager::setScrollCallback(std::function<void(double)> callback) {
        m_scrollCallback = std::move(callback);
    }
//-------------------------------------------------------------------------------

    // Event callbacks
    void InputManager::onKeyEvent(int key, int action) {
        std::cout << "KeyEvent method of Input called \n";
        if (m_keyMap.find(key) == m_keyMap.end()) return;


        KeyCode keyCode = m_keyMap[key];
        int index = static_cast<int>(keyCode);

        if (action == 1) { // Pressed
            m_keyStates[index] = InputState::JUST_PRESSED;
        } else if (action == 0) { // Released
            m_keyStates[index] = InputState::JUST_RELEASED;
        }

        if (m_keyCallback) {
            m_keyCallback(keyCode, m_keyStates[index]);
        }
    }

    void InputManager::onMouseButtonEvent(int button, int action) {
        std::cout << "MouseButtonEvent method of Input called \n";
        if (m_mouseMap.find(button) == m_mouseMap.end()) return;

        KeyCode buttonCode = m_mouseMap[button];
        int index = static_cast<int>(buttonCode);

        if (action == 1) {
            m_keyStates[index] = InputState::JUST_PRESSED;
        } else if (action == 0) {
            m_keyStates[index] = InputState::JUST_RELEASED;
        }

        if (m_mouseCallback) {
            m_mouseCallback(buttonCode, m_keyStates[index]);
        }
    }

    void InputManager::onMouseMoveEvent(double x, double y) {
        std::cout << "MouseMoveEvent method of Input called \n";
        vec2 newPos(static_cast<float>(x), static_cast<float>(y));
        m_mouseDelta = newPos - m_mousePosition;
        m_mousePosition = newPos;
    }

    void InputManager::onScrollEvent(double xoffset, double yoffset) {
        std::cout << "ScrollEvent method of Input called \n";
        m_scrollDelta = static_cast<float>(yoffset);

        if (m_scrollCallback) {
            m_scrollCallback(yoffset);
        }
    }



    void InputManager::setupKeyMappings() {
        // Alphabet
        m_keyMap[0x41] = KeyCode::KEY_A;
        m_keyMap[0x42] = KeyCode::KEY_B;
        m_keyMap[0x43] = KeyCode::KEY_C;
        m_keyMap[0x44] = KeyCode::KEY_D;
        m_keyMap[0x45] = KeyCode::KEY_E;
        m_keyMap[0x46] = KeyCode::KEY_F;
        m_keyMap[0x47] = KeyCode::KEY_G;
        m_keyMap[0x48] = KeyCode::KEY_H;
        m_keyMap[0x49] = KeyCode::KEY_I;
        m_keyMap[0x4A] = KeyCode::KEY_J;
        m_keyMap[0x4B] = KeyCode::KEY_K;
        m_keyMap[0x4C] = KeyCode::KEY_L;
        m_keyMap[0x4D] = KeyCode::KEY_M;
        m_keyMap[0x4E] = KeyCode::KEY_N;
        m_keyMap[0x4F] = KeyCode::KEY_O;
        m_keyMap[0x50] = KeyCode::KEY_P;
        m_keyMap[0x51] = KeyCode::KEY_Q;
        m_keyMap[0x52] = KeyCode::KEY_R;
        m_keyMap[0x53] = KeyCode::KEY_S;
        m_keyMap[0x54] = KeyCode::KEY_T;
        m_keyMap[0x55] = KeyCode::KEY_U;
        m_keyMap[0x56] = KeyCode::KEY_V;
        m_keyMap[0x57] = KeyCode::KEY_W;
        m_keyMap[0x58] = KeyCode::KEY_X;
        m_keyMap[0x59] = KeyCode::KEY_Y;
        m_keyMap[0x5A] = KeyCode::KEY_Z;


        // Numbers
        m_keyMap[0x30] = KeyCode::KEY_0;
        m_keyMap[0x31] = KeyCode::KEY_1;
        m_keyMap[0x32] = KeyCode::KEY_2;
        m_keyMap[0x33] = KeyCode::KEY_3;
        m_keyMap[0x34] = KeyCode::KEY_4;
        m_keyMap[0x35] = KeyCode::KEY_5;
        m_keyMap[0x36] = KeyCode::KEY_6;
        m_keyMap[0x37] = KeyCode::KEY_7;
        m_keyMap[0x38] = KeyCode::KEY_8;
        m_keyMap[0x39] = KeyCode::KEY_9;
        // Function keys
        m_keyMap[VK_F1] = KeyCode::KEY_F1;
        m_keyMap[VK_F2] = KeyCode::KEY_F2;
        m_keyMap[VK_F3] = KeyCode::KEY_F3;
        m_keyMap[VK_F4] = KeyCode::KEY_F4;
        m_keyMap[VK_F5] = KeyCode::KEY_F5;
        m_keyMap[VK_F6] = KeyCode::KEY_F6;
        m_keyMap[VK_F7] = KeyCode::KEY_F7;
        m_keyMap[VK_F8] = KeyCode::KEY_F8;
        m_keyMap[VK_F9] = KeyCode::KEY_F9;
        m_keyMap[VK_F10] = KeyCode::KEY_F10;
        m_keyMap[VK_F11] = KeyCode::KEY_F11;
        m_keyMap[VK_F12] = KeyCode::KEY_F12;
        // Special keys
        m_keyMap[VK_SPACE]     = KeyCode::KEY_SPACE;
        m_keyMap[VK_RETURN]    = KeyCode::KEY_ENTER;
        m_keyMap[VK_ESCAPE]    = KeyCode::KEY_ESCAPE;
        m_keyMap[VK_BACK]      = KeyCode::KEY_BACKSPACE;
        m_keyMap[VK_TAB]       = KeyCode::KEY_TAB;
        m_keyMap[VK_SHIFT]     = KeyCode::KEY_SHIFT;
        m_keyMap[VK_CONTROL]   = KeyCode::KEY_CTRL;
        m_keyMap[VK_MENU]      = KeyCode::KEY_ALT;
        m_keyMap[VK_CAPITAL]   = KeyCode::KEY_CAPSLOCK;
        m_keyMap[VK_INSERT]    = KeyCode::KEY_INSERT;
        m_keyMap[VK_DELETE]    = KeyCode::KEY_DELETE;
        m_keyMap[VK_HOME]      = KeyCode::KEY_HOME;
        m_keyMap[VK_END]       = KeyCode::KEY_END;
        m_keyMap[VK_PRIOR]     = KeyCode::KEY_PAGEUP;
        m_keyMap[VK_NEXT]      = KeyCode::KEY_PAGEDOWN;
        // Arrow keys
        m_keyMap[VK_UP]        = KeyCode::KEY_UP;
        m_keyMap[VK_DOWN]      = KeyCode::KEY_DOWN;
        m_keyMap[VK_LEFT]      = KeyCode::KEY_LEFT;
        m_keyMap[VK_RIGHT]     = KeyCode::KEY_RIGHT;
        // Numpad
        m_keyMap[VK_NUMPAD0] = KeyCode::KEY_NUMPAD_0;
        m_keyMap[VK_NUMPAD1] = KeyCode::KEY_NUMPAD_1;
        m_keyMap[VK_NUMPAD2] = KeyCode::KEY_NUMPAD_2;
        m_keyMap[VK_NUMPAD3] = KeyCode::KEY_NUMPAD_3;
        m_keyMap[VK_NUMPAD4] = KeyCode::KEY_NUMPAD_4;
        m_keyMap[VK_NUMPAD5] = KeyCode::KEY_NUMPAD_5;
        m_keyMap[VK_NUMPAD6] = KeyCode::KEY_NUMPAD_6;
        m_keyMap[VK_NUMPAD7] = KeyCode::KEY_NUMPAD_7;
        m_keyMap[VK_NUMPAD8] = KeyCode::KEY_NUMPAD_8;
        m_keyMap[VK_NUMPAD9] = KeyCode::KEY_NUMPAD_9;
        // Mouse buttons
        m_mouseMap[VK_LBUTTON] = KeyCode::MOUSE_LEFT;
        m_mouseMap[VK_RBUTTON] = KeyCode::MOUSE_RIGHT;
        m_mouseMap[VK_MBUTTON] = KeyCode::MOUSE_MIDDLE;
        m_mouseMap[VK_XBUTTON1] = KeyCode::MOUSE_BUTTON_4;
        m_mouseMap[VK_XBUTTON2] = KeyCode::MOUSE_BUTTON_5;
    }


}

