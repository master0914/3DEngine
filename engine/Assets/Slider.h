//
// Created by augus on 10.03.2026.
//

#ifndef INC_3DENGINE_SLIDER_H
#define INC_3DENGINE_SLIDER_H
#include <assert.h>

#include "IComponent.h"

#endif //INC_3DENGINE_SLIDER_H

// config mit resolution
template<typename T>
struct SliderConfigWithResolution{
    ivec2 pos = ivec2(0, 0);
    ivec2 size = ivec2(50, 30);
    int sliderWidth = 20;
    uint32_t backgroundColor = 0xff666666;
    uint32_t sliderColor = 0xff000000;
    T from = T{0};
    T to = T{100};
    int resolution = 100;
};

// config mit stepSize
template<typename T>
struct SliderConfigWithStepSize{
    ivec2 pos = ivec2(0, 0);
    ivec2 size = ivec2(50, 30);
    int sliderWidth = 20;
    uint32_t backgroundColor = 0xff666666;
    uint32_t sliderColor = 0xff000000;
    T from = T{0};
    T to = T{100};
    T stepSize = T{1};
};

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

    // konstruktor bsp
    // Slider<float> slider = Slider<float>(m_context,m_container,SliderConfigWithStepSize<float>{
    //     .pos = {100, 200},
    //     .size = {500, 40},
    //     .sliderWidth = 20,
    //     .backgroundColor = 0xffff0000,
    //     .sliderColor = 0xff0000ff,
    //     .from = 0.0f,
    //     .to = 10.0f,
    //     .stepSize = 1
    // });
    Slider(Engine::EngineContext &context, Engine::GameContainer &container, const SliderConfigWithResolution<T>& config = {}) // NOLINT(*-pro-type-member-init)
        : IComponent(context, container, config.pos, config.size) {
        m_sliderSize = ivec2(config.sliderWidth, m_size.y);
        setColors(config.backgroundColor, config.sliderColor);
        setRange(config.from, config.to, config.resolution);
    }
    Slider(Engine::EngineContext &context, Engine::GameContainer &container, const SliderConfigWithStepSize<T>& config = {}) // NOLINT(*-pro-type-member-init)
        : IComponent(context, container, config.pos, config.size) {
        m_sliderSize = ivec2(config.sliderWidth, m_size.y);
        setColors(config.backgroundColor, config.sliderColor);
        setRangeWithStepSize(config.from, config.to, config.stepSize);
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
    // size of the Slider Overlay is stored in parent IComponent

    // size of actual Slider
    ivec2 m_sliderPos;
    ivec2 m_sliderSize;

    uint32_t m_backgroundColor;
    uint32_t m_sliderColor;

    T m_currentValue;
    T m_valueFrom;
    T m_valueTo;
    int m_stepResolution;   // how many steps in between To and From
    T m_stepSize;

    bool m_isDragging = false;

    void setRange(T from, T to, int resolution) {
        if (resolution < 1) {
            LOG_WARN("Resolution 0 or smaller results in undefined behavior. Will be set to 1");
            resolution = 1;
        }
        m_valueFrom = from;
        m_valueTo = to;
        m_stepResolution = resolution;
        m_stepSize = (to - from) / resolution;
        m_currentValue = from;
        updateSliderPositionFromValue();
    }
    void setRangeWithStepSize(T from, T to, T stepSize) {
        if (stepSize < 1) {
            LOG_WARN("stepSize 0 or smaller results in undefined behavior. Will be set to 1");
            stepSize = 1;
        }
        m_valueFrom = from;
        m_valueTo = to;
        m_stepSize = stepSize;
        m_stepResolution = static_cast<int>((to - from) / stepSize);
        m_currentValue = from;
        updateSliderPositionFromValue();
    }

    void setColors(const uint32_t backgroundColor, const uint32_t sliderColor) {
        m_backgroundColor = backgroundColor;
        m_sliderColor = sliderColor;
    }

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
