//
// Created by augus on 03.06.2026.
//

#ifndef INC_3DENGINE_MIXINGSTATION_H
#define INC_3DENGINE_MIXINGSTATION_H

#endif //INC_3DENGINE_MIXINGSTATION_H

#pragma once
#include "../../../engine/Assets/Slider.h"
#include "../../../engine/Assets/Button.h"
#include "../../../engine/Assets/textField.h"
#include "../../../engine/Assets/DragField.h"
#include "OscillatorControl.h"



class MixingStationGame : public Engine::IGame {
public:
    explicit MixingStationGame(Engine::EngineContext& context, Engine::GameContainer& container)
        : IGame(context, container) {
        addOscButton.setOnClick([this]() {
            addOscillator();
            isDirty = true;
        });
        playButton.setOnClick([this]() {
            isPlaying = !isPlaying;
            playButton.setText(isPlaying ? "Stop All" : "Play All");
            playButton.setButtonColor(isPlaying ? 0xff552222 : 0xff225522);
        });
    }

    void update(float dt) override {
        addOscButton.update(dt);
        playButton.update(dt);
        volumeSlider.update(dt);

        if (pendingRemoval >= 0) {
            size_t idx = pendingRemoval;
            pendingRemoval = -1;
            removeOscillator(idx);
        }

        for (auto& osc : oscillators) {
            osc -> update(dt);
            if (osc->isDirty()) {
                isDirty = true;
            }
        }
    }

    void render() override {
        addOscButton.render();
        playButton.render();
        volumeSlider.render();

        for (auto& osc : oscillators) {
            osc->render();
        }
    }

    void onInit() override {}
    void onExit() override {}
    void handleInput(float dt);

private:

    void addOscillator() {
        int yPos = 160 + oscillators.size() * 80;
        auto osc = std::make_unique<OscillatorControl>(m_context, m_container, yPos);

        // remove callback set and updates the pending removal
        osc->removeButton.setOnClick([this, idx = oscillators.size()]() {
            // removeOscillator(idx);
                LOG_INFO("removal of osc: " + std::to_string(idx));
                pendingRemoval = idx; // NOLINT(*-narrowing-conversions)
        });

        oscillators.push_back(std::move(osc));
        isDirty = true;
    }

    void removeOscillator(size_t index) {
        if (index < oscillators.size()) {
            oscillators.erase(oscillators.begin() + index);
            for (size_t i = index; i < oscillators.size(); ++i) {
                // oscillators[i]->yOffset = 160 + i * 80;
                oscillators[i]->reposition(160 + i * 80);

                // update callbacks for new indices
                oscillators[i]->removeButton.setOnClick([this, i]() {
                    LOG_INFO("removal of osc: " + std::to_string(i));
                    pendingRemoval = i;
                });
            }
            isDirty = true;
        }
    }

    // setters/getters
public:

    [[nodiscard]] std::vector<OscillatorSettings> getOscillatorSettings() const {
        std::vector<OscillatorSettings> settings;
        for (const auto& osc : oscillators) {
            settings.push_back({
                osc->getFrequencyOfOsc(),
                osc->getWaveType() == WaveType::Sine
            });
        }
        return settings;
    }

    float getMasterVolume() {
        return volumeSlider.getCurrentValue();
    }

    [[nodiscard]] bool isPlayingActive() const {
        return isPlaying;
    }

    // yeah i know not the best names XD
    [[nodiscard]] bool isStationDirty() const {
        return isDirty;
    }
    void cleanStation() {
        for (const auto& osc: oscillators) {
            osc->cleanOscillator();
        }
        isDirty = false;
    }

private:
    Button addOscButton = Button{m_context, m_container, {
        .pos = {10, 10},
        .padding = {10, 10},
        .buttonColor = 0xff444444,
        .textColor = 0xffffffff,
        .filled = true,
        .text = "+ Add Oscillator"
    }};
    Button playButton = Button{m_context, m_container, {
        .pos = {10, 60},
        .padding = {10, 10},
        .buttonColor = 0xff225522,
        .textColor = 0xffffffff,
        .filled = true,
        .text = "Play All"
    }};
    Slider<float> volumeSlider = Slider<float>{m_context, m_container, SliderConfigWithStepSize<float>{
        .pos = {10, 120},
        .size = {200, 30},
        .sliderWidth = 15,
        .backgroundColor = 0xff333333,
        .sliderColor = 0xff666666,
        .from = 0.0f,
        .to = 1.0f,
        .stepSize = 0.01f
    }};
    std::vector<std::unique_ptr<OscillatorControl>> oscillators;
    bool isPlaying = false;
    bool isDirty = false;

    int pendingRemoval = -1;
};