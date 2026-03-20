//
// Created by augus on 18.03.2026.
//

#ifndef INC_3DENGINE_TEXTFIELD_H
#define INC_3DENGINE_TEXTFIELD_H
#pragma once
#include "IComponent.h"

#endif //INC_3DENGINE_TEXTFIELD_H

// @TODO continue

struct TextFieldConfig{
    ivec2 pos = {0,0};
    ivec2 size = {50,20};
    bool fillTextField = true;
    uint32_t backgroundColor = 0xff111111;
    uint32_t textColor = 0xffffffff;
    bool renderInputPrompt = false;
    std::string inputPrompt;
    int maxCharacters = 0;
};
class TextField: Engine::IComponent {
public:
    TextField(Engine::EngineContext &context, Engine::GameContainer &container, const TextFieldConfig& config = {}): IComponent(context,container, config.pos, config.size) {

        m_fillTextField = config.fillTextField;
        m_backgroundColor = config.backgroundColor;
        m_textColor = config.textColor;
        m_renderInputPrompt = config.renderInputPrompt;   // the blinking bar that suggests input
        m_inputPrompt = config.inputPrompt;          // actual inputPrompt like:  "> "
        m_maxCharacters = config.maxCharacters;

        m_paddingY = (m_size.y - m_context.renderer2D->getFont()->getTextSize("A").y) / 2 + 1;

        m_textInputListener = [this](const char* text) {
            if (m_inFokus) {
                if (m_text.length() < m_maxCharacters) {
                    m_text.append(text);
                }
            }
        };
    }

    void registerCallback() const {
        m_context.input->addTextInputListener(m_textInputListener);
    }

    void update(float dt) override {
        if (m_context.input->isKeyJustPressed(Engine::KeyCode::KEY_BACKSPACE)) {
            if (!m_text.empty()) {
                m_text.pop_back();
            }
        }
        if (m_context.input->isKeyJustPressed(Engine::KeyCode::KEY_ENTER)) {
            m_inFokus = false;
        }
        if (hoversOver() && m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
            m_inFokus = true;
        }
        if (!hoversOver() && m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
            m_inFokus = false;
        }
    }

    void render() override {
        if (m_fillTextField) {m_context.renderer2D->fillRectangle(m_pos,m_size.y, m_size.x, m_backgroundColor);}
        else {m_context.renderer2D->drawRectangle(m_pos,m_size.y, m_size.x, m_backgroundColor);}
        m_context.renderer2D->drawText(m_inputPrompt + m_text, m_pos.x, m_pos.y + m_paddingY, m_textColor);
    }
private:
    // Parameters
    std::string m_text;
    int m_maxCharacters = 0;
    bool m_fillTextField;
    uint32_t m_backgroundColor;
    uint32_t m_textColor;
    bool m_renderInputPrompt = false;   // the blinking bar that suggests input
    std::string m_inputPrompt;          // actual inputPrompt like:  "> "
    // runtime variables
    bool m_inFokus = false;
    int m_paddingY;
    std::function<void(const char*)> m_textInputListener;
};


