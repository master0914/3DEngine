//
// Created by Master0914 on 11.09.2025.
//
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
        vec2 newPos(static_cast<float>(x), static_cast<float>(y));
        m_mouseDelta = newPos - m_mousePosition;
        m_mousePosition = newPos;
    }

    void InputManager::onScrollEvent(double xoffset, double yoffset) {
        m_scrollDelta = static_cast<float>(yoffset);

        if (m_scrollCallback) {
            m_scrollCallback(yoffset);
        }
    }


}

