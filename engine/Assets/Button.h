//
// Created by augus on 09.03.2026.
//

#ifndef INC_3DENGINE_BUTTON_H
#define INC_3DENGINE_BUTTON_H
#pragma once
#include "IComponent.h"
#include "vector.h"
#include "../core/util/colors.h"

#endif //INC_3DENGINE_BUTTON_H

class Button: public Engine::IComponent {
    public:
        // full constructor
        Button(Engine::EngineContext &context, Engine::GameContainer &container, ivec2 pos, ivec2 padding, uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text)
            : IComponent(context, container), m_padding(padding){
            setParameters(buttonColor, textColor, filled, text);
            m_pos = pos;
        }
        Button(Engine::EngineContext &context, Engine::GameContainer &container, int x, int y, int w, int h, uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text)
            : IComponent(context, container), m_padding(ivec2{w,h}) {
            setParameters(buttonColor, textColor, filled, text);
            m_pos = ivec2{x,y};
        }
        // constructor with pos and padding
        Button(Engine::EngineContext &context, Engine::GameContainer &container, ivec2 pos, ivec2 padding)
            : IComponent(context, container), m_padding(padding) {
            m_pos = pos;
        }
        Button(Engine::EngineContext &context, Engine::GameContainer &container, int x, int y, int w, int h)
            : IComponent(context, container), m_padding(ivec2{w,h}) {
            m_pos = ivec2{x,y};
        }
        // constructor only with pos
        Button(Engine::EngineContext &context, Engine::GameContainer &container, ivec2 pos)
            : IComponent(context, container) {
            m_pos = pos;
        }
        Button(Engine::EngineContext &context, Engine::GameContainer &container, int x, int y)
            : IComponent(context, container) {
            m_pos = ivec2{x,y};
        }

        void setParameters(uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text) {
            m_buttonColor = buttonColor;
            m_textColor = textColor;
            m_filled = filled;
            m_text = text;
            m_textSize = m_context.renderer2D->getFont()->getTextSize(m_text);
            m_size = m_textSize + (m_padding * 2);
        }

        using Callback = std::function<void()>;

        void setOnClick(Callback cb){ m_onClick = std::move(cb); }

        void update(float dt) override{
            if (clickedOnButton()) {
                if (m_onClick) {
                    m_onClick();
                }
            }
        }

        void render() override {
            if (!m_filled) {
                m_context.renderer2D->drawRectangle(m_pos,m_size.y, m_size.x + 1, m_buttonColor);
            }
            else {
                m_context.renderer2D->fillRectangle(m_pos,m_size.y, m_size.x + 1, m_buttonColor);
            }
            m_context.renderer2D->drawText(m_text,m_pos.x + m_padding.x + 1, m_pos.y + m_padding.y + 1, m_textColor);
        }

        [[nodiscard]] bool hoversOverButton() const {
            ivec2 mousePos = m_context.input->getMousePositionIvec();
            if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + m_size.x
                && mousePos.y > m_pos.y && mousePos.y < m_pos.y + m_size.y) {
                return true;
            }
            return false;
        }
        // uses JustPressed so will not activate when held down
        [[nodiscard]] bool clickedOnButton() const {
            if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
                if (hoversOverButton()) {
                    return true;
                }
            }
            return false;
        }
    private:
        Callback m_onClick;
        ivec2 m_padding = ivec2(5,5);
        // parameters
        uint32_t m_buttonColor = Colors::WHITE;
        uint32_t m_textColor = Colors::BLACK;
        bool m_filled = false;
        std::string m_text;
        // calculated parameters
        ivec2 m_textSize = ivec2();
};