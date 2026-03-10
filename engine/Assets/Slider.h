//
// Created by augus on 10.03.2026.
//

#ifndef INC_3DENGINE_SLIDER_H
#define INC_3DENGINE_SLIDER_H
#include "IComponent.h"

#endif //INC_3DENGINE_SLIDER_H
template<typename T>
class Slider: Engine::IComponent{
public:
    // Shematic:
    //  |-> Slider Overlay(pos,size)
    //  -------------------------------------
    //  |     |                             |
    //  |     |-------------------------    |
    //  |     |                             |
    //  -------------------------------------
    //        |-> slider component(sliderPos,sliderSize)
    Slider(Engine::EngineContext &context, Engine::GameContainer &container, ivec2 pos, ivec2 size)
        : IComponent(context, container), m_pos(pos), m_size(size){
        m_sliderSize = ivec2(20, size.y);
    }

    void setRange(T from, T to, int resolution) {
        m_valueFrom = from;
        m_valueTo = to;
        m_stepResolution = resolution;
        m_stepSize = (to - from) / resolution;
        m_currentValue = from;
        updateSliderPositionFromValue();
    }
    void setRangeWithStepSize(T from, T to, T stepSize) {
        m_valueFrom = from;
        m_valueTo = to;
        m_stepSize = stepSize;
        m_stepResolution = static_cast<int>((to - from) / stepSize);
        m_currentValue = from;
        updateSliderPositionFromValue();
    }

    void update(float dt) override {
        handleSliderInteraction();
    }

    void render() override {
        m_context.renderer2D->fillRectangle(m_pos,m_size.y,m_size.x,0xffffffff);
        m_context.renderer2D->fillRectangle(m_sliderPos,m_sliderSize.y,m_sliderSize.x,0xffff0000);
    }

    void onInit() override{}

    void onExit() override{}

    T getCurrentValue() {return m_currentValue;}


private:
    // size of the Slider Overlay
    ivec2 m_pos;
    ivec2 m_size;
    // size of actual Slider
    ivec2 m_sliderPos;
    ivec2 m_sliderSize;

    T m_currentValue;
    T m_valueFrom;
    T m_valueTo;
    int m_stepResolution;   // how many steps in between To and From
    T m_stepSize;

    bool m_isDragging = false;

    void handleSliderInteraction() {
        if (clickingOnSliderComponent()) {
            m_isDragging = true;
        }

        if (m_isDragging) {
            if (m_context.input->isMouseButtonJustReleased(Engine::KeyCode::MOUSE_LEFT)) {
                m_isDragging = false;
                return;
            }

            ivec2 mousePos = m_context.input->getMousePositionIvec();

            int minX = m_pos.x;
            int maxX = m_pos.x + m_size.x - m_sliderSize.x;

            int newSliderX = std::clamp(mousePos.x - m_sliderSize.x/2, minX, maxX);

            setValueFromSliderX(newSliderX);
        }
    }

    void setValueFromSliderX(int sliderX) {
        // normalize pos
        int minX = m_pos.x;
        int maxX = m_pos.x + m_size.x - m_sliderSize.x;
        float normalized = static_cast<float>(sliderX - minX) / static_cast<float>(maxX - minX);

        // step Rounding
        T rawValue = m_valueFrom + normalized * (m_valueTo - m_valueFrom);

        // apply stepSize
        if (m_stepSize > 0) {
            float steps = std::round((rawValue - m_valueFrom) / m_stepSize);
            m_currentValue = m_valueFrom + steps * m_stepSize;

            // Clamping
            if (m_currentValue < m_valueFrom) m_currentValue = m_valueFrom;
            if (m_currentValue > m_valueTo) m_currentValue = m_valueTo;
        } else {
            m_currentValue = rawValue;
        }

        // update the sliderPos
        updateSliderPositionFromValue();
    }

    void updateSliderPositionFromValue() {
        // normalize pos
        float normalized = static_cast<float>(m_currentValue - m_valueFrom) /
                          (m_valueTo - m_valueFrom);


        int minX = m_pos.x;
        int maxX = m_pos.x + m_size.x - m_sliderSize.x;

        m_sliderPos.x = minX + static_cast<int>(normalized * static_cast<float>(maxX - minX));
        m_sliderPos.y = m_pos.y;
    }

    [[nodiscard]] bool hoversOverSliderComponent() const {
        ivec2 mousePos = m_context.input->getMousePositionIvec();
        if (mousePos.x > m_sliderPos.x && mousePos.x < m_sliderPos.x + m_sliderSize.x
            && mousePos.y > m_sliderPos.y && mousePos.y < m_sliderPos.y + m_sliderSize.y) {
            return true;
            }
        return false;
    }

    // uses Pressed so will activate when held down
    [[nodiscard]] bool clickingOnSliderComponent() const {
        if (m_context.input->isMouseButtonPressed(Engine::KeyCode::MOUSE_LEFT)) {
            if (hoversOverSliderComponent()) {
                return true;
            }
        }
        return false;
    }
};
