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
        Button(Engine::EngineContext &context, Engine::GameContainer &container, vec2 pos, vec2 padding, uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text)
            : IComponent(context, container), m_pos(pos), m_padding(padding) {
            setParameters(buttonColor, textColor, filled, text);
        }
        Button(Engine::EngineContext &context, Engine::GameContainer &container, int x, int y, int w, int h, uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text)
            : IComponent(context, container), m_pos(vec2{x,y}), m_padding(vec2{w,h}) {
            setParameters(buttonColor, textColor, filled, text);
        }

        void setParameters(uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text) {
            m_buttonColor = buttonColor;
            m_textColor = textColor;
            m_filled = filled;
            m_text = text;
            m_textSize = m_context.renderer2D->getFont()->getTextSize(m_text);
            m_finalButtonSize = m_textSize + (m_padding * 2);
        }

        using Callback = std::function<void()>;

        void setOnClick(Callback cb){ m_onClick = std::move(cb); }

        void update(float dt) override{
            if (clickedOnButton()) {
                if (m_onClick) {
                    std::cout << "clock";
                    m_onClick();
                }
            }
        }

        void render() override {
            if (!m_filled) {
                m_context.renderer2D->drawRectangle(m_pos,m_finalButtonSize.y, m_finalButtonSize.x + 1, m_buttonColor);
            }
            else {
                m_context.renderer2D->fillRectangle(m_pos,m_finalButtonSize.y, m_finalButtonSize.x + 1, m_buttonColor);
            }
            m_context.renderer2D->drawText(m_text,m_pos.x + m_padding.x + 1, m_pos.y + m_padding.y + 1, m_textColor);
        }

        bool hoversOverButton() const {
            vec2 mousePos = m_context.input->getMousePosition();
            if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + m_finalButtonSize.x
                && mousePos.y > m_pos.y && mousePos.y < m_pos.y + m_finalButtonSize.y) {
                return true;
            }
            return false;
        }

        bool clickedOnButton() const {
            if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
                if (hoversOverButton()) {
                    return true;
                }
            }
            return false;
        }
    private:
        Callback m_onClick;
        vec2 m_pos;
        vec2 m_padding;
        // parameters
        uint32_t m_buttonColor = Colors::BLUE;
        uint32_t m_textColor = Colors::WHITE;
        bool m_filled = false;
        std::string m_text = "";
        // calculated parameters
        vec2 m_textSize = vec2();
        vec2 m_finalButtonSize = vec2();
};