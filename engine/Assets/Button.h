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
using Callback = std::function<void()>;

struct ButtonConfig {
    ivec2 pos = ivec2(0, 0);
    ivec2 padding = ivec2(5,5);
    uint32_t buttonColor = Colors::WHITE;
    uint32_t textColor = Colors::BLACK;
    bool filled = false;
    std::string text;
};

class Button: public Engine::IComponent {
public:
    // konsturktor bsp
    // Button button = Button{m_context,m_container,{
    //     .pos = {100,100},
    //     .padding = {250,250},
    //     .buttonColor = 0xff333333,
    //     .textColor = 0xffffffff,
    //     .filled = true,
    //     .text = "hello"
    // }};
    Button(Engine::EngineContext &context, Engine::GameContainer &container, const ButtonConfig& config = {})
        : IComponent(context, container), m_padding(config.padding){
        setParameters(config.buttonColor, config.textColor, config.filled, config.text);
        m_pos = config.pos;
    }


    void setParameters(uint32_t buttonColor, uint32_t textColor, bool filled, const std::string& text) {
        m_buttonColor = buttonColor;
        m_textColor = textColor;
        m_filled = filled;
        m_text = text;
        m_textSize = m_context.renderer2D->getFont()->getTextSize(m_text);
        m_size = m_textSize + (m_padding * 2);
    }



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

    // uses JustPressed so will not activate when held down
    [[nodiscard]] bool clickedOnButton() const {
        if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
            if (hoversOver()) {
                return true;
            }
        }
        return false;
    }
};