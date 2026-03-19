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
    ivec2 pos;
    ivec2 size;
    ivec2 padding;
    bool fillTextField = true;
    uint32_t color = 0xff000000;
    bool renderInputPrompt = false;
    std::string inputPrompt;
    int maxCharacters = 0;
};
class TextField: Engine::IComponent {
public:
    TextField(Engine::EngineContext &context, Engine::GameContainer &container, ivec2 pos, ivec2 size): IComponent(context,container, pos, size) {
        m_textInputListener = [this](const char* text) {
            m_text.append(text);
        };
    }

    void registerCallback() const {
        m_context.input->addTextInputListener(m_textInputListener);
    }

    void update(float dt) override{}

    void render() override {
        m_context.renderer2D->drawText(m_text, m_pos, 0xffffffff);
    }
private:
    std::string m_text;

    int m_maxCharacters = 0;

    bool m_fillTextField;
    uint32_t color;

    bool m_renderInputPrompt = false;
    std::string m_inputPrompt;

    std::function<void(const char*)> m_textInputListener;
};


