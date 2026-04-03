//
// Created by augus on 03.04.2026.
//

#ifndef INC_3DENGINE_DRAGFIELD_H
#define INC_3DENGINE_DRAGFIELD_H
#pragma once
#include <cstdint>

#include "IComponent.h"
#include "vector.h"

#endif //INC_3DENGINE_DRAGFIELD_H

template<typename T>
struct DragFieldConfig {
    ivec2 pos = ivec2(0, 0);
    ivec2 size = ivec2(80, 20);
    uint32_t backgroundColor = 0xff666666;
    uint32_t textColor = 0xffffffff;
    T from = T{0};
    T to = T{100};
    T stepSize = T{1};
    std::string label;
};

template<typename T>
class DragField : Engine::IComponent {
public:
    DragField(Engine::EngineContext &context, Engine::GameContainer &container, const DragFieldConfig<T> &config = {})
        : IComponent(context, container, config.pos, config.size) {
        m_backgroundColor = config.backgroundColor;
        m_textColor = config.textColor;
        m_valueFrom = config.from;
        m_valueTo = config.to;
        m_stepSize = config.stepSize;
        m_currentValue = config.from;
        m_label = config.label;
    }

    void update(float dt) override {
        ivec2 mousePos = m_context.input->getMousePositionIvec();

        if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT) && hoversOver()) {
            m_isDragging = true;
            m_dragStartX = mousePos.x;
            m_dragStartValue = m_currentValue;
        }

        if (m_context.input->isMouseButtonJustReleased(Engine::KeyCode::MOUSE_LEFT)) {
            m_isDragging = false;
        }

        if (m_isDragging) {
            int delta = mousePos.x - m_dragStartX;
            T rawValue = m_dragStartValue + static_cast<T>(delta) * m_stepSize;
            float steps = std::round(static_cast<float>(rawValue - m_valueFrom) / static_cast<float>(m_stepSize));
            m_currentValue = m_valueFrom + static_cast<T>(steps) * m_stepSize;
            m_currentValue = std::clamp(m_currentValue, m_valueFrom, m_valueTo);
        }
    }

    void render() override {
        m_context.renderer2D->fillRectangle(m_pos, m_size.y, m_size.x, m_backgroundColor);

        std::ostringstream oss;
        if (!m_label.empty()) oss << m_label << ": ";
        oss << m_currentValue;

        ivec2 textSize = m_context.renderer2D->getFont()->getTextSize(oss.str());
        ivec2 textPos = {
            m_pos.x + (m_size.x - textSize.x) / 2,
            m_pos.y + (m_size.y - textSize.y) / 2
        };
        m_context.renderer2D->drawText(oss.str(), textPos, m_textColor);
    }

    void onInit() override {}
    void onExit() override {}

    T getCurrentValue() { return m_currentValue; }
    void setValue(T value) { m_currentValue = std::clamp(value, m_valueFrom, m_valueTo); }

private:
    uint32_t m_backgroundColor;
    uint32_t m_textColor;
    T m_currentValue;
    T m_valueFrom;
    T m_valueTo;
    T m_stepSize;
    std::string m_label;

    bool m_isDragging = false;
    int m_dragStartX = 0;
    T m_dragStartValue = T{};
};