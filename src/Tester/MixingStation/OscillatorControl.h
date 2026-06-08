//
// Created by augus on 05.06.2026.
//

#ifndef INC_3DENGINE_OSCILLATORCONTROL_H
#define INC_3DENGINE_OSCILLATORCONTROL_H

#endif //INC_3DENGINE_OSCILLATORCONTROL_H
#pragma once
#include "MixingStation.h"

struct OscillatorSettings {
    float frequency;
    bool isSine; // true = sine, false = saw
};

enum class WaveType {
    Sine, Saw
};

struct OscillatorControl {
    Note currentNote = Note::C;
    int octave = 4;
    WaveType waveType = WaveType::Sine;
    bool useCustomFreq = false;
    float customFreq = 261.63f; // Middle C
    int yOffset;
    bool dirty = false;

    // Note selection buttons
    Button noteDown;
    Button noteUp;
    Button octaveDown;
    Button octaveUp;
    Button waveToggle;
    Button removeButton;
    TextField customFreqField;



    Engine::EngineContext m_context;

    OscillatorControl(Engine::EngineContext& context, Engine::GameContainer& container, int y)
        : yOffset(y), m_context(context),
          noteDown(context, container, {
              .pos = {150, yOffset + 5},
              .padding = {8, 5},
              .buttonColor = 0xff444444,
              .textColor = 0xffffffff,
              .filled = true,
              .text = "< Note"
          }),
          noteUp(context, container, {
              .pos = {230, yOffset + 5},
              .padding = {8, 5},
              .buttonColor = 0xff444444,
              .textColor = 0xffffffff,
              .filled = true,
              .text = "Note >"
          }),
          octaveDown(context, container, {
              .pos = {150, yOffset + 40},
              .padding = {8, 5},
              .buttonColor = 0xff444444,
              .textColor = 0xffffffff,
              .filled = true,
              .text = "< Oct"
          }),
          octaveUp(context, container, {
              .pos = {230, yOffset + 40},
              .padding = {8, 5},
              .buttonColor = 0xff444444,
              .textColor = 0xffffffff,
              .filled = true,
              .text = "Oct >"
          }),
          waveToggle(context, container, {
              .pos = {320, yOffset + 5},
              .padding = {8, 5},
              .buttonColor = 0xff444488,
              .textColor = 0xffffffff,
              .filled = true,
              .text = "Sine"
          }),
          removeButton(context, container, {
              .pos = {520, yOffset + 5},
              .padding = {8, 5},
              .buttonColor = 0xff882222,
              .textColor = 0xffffffff,
              .filled = true,
              .text = "X"
          }),
          customFreqField(context, container, TextFieldConfig{
              .pos = {400, yOffset + 5},
              .size = {100, 30},
              .fillTextField = true,
              .backgroundColor = 0xff333333,
              .textColor = 0xff00ff00,
              .renderInputPrompt = true,
              .inputPrompt = "Hz: ",
              .maxCharacters = 7
          }) {

        customFreqField.registerCallback();

        // Note buttons
        noteDown.setOnClick([this]() {
            if (!useCustomFreq) {
                if (currentNote == Note::C) {
                    currentNote = Note::B;
                    octave--;
                } else {
                    currentNote = static_cast<Note>(static_cast<int>(currentNote) - 1);
                }
                updateFrequencyFromNote();
            }
        });

        noteUp.setOnClick([this]() {
            if (!useCustomFreq) {
                if (currentNote == Note::B) {
                    currentNote = Note::C;
                    octave++;
                } else {
                    currentNote = static_cast<Note>(static_cast<int>(currentNote) + 1);
                }
                updateFrequencyFromNote();
            }
        });

        // Octave buttons
        octaveDown.setOnClick([this]() {
            if (!useCustomFreq && octave > 0) {
                octave--;
                updateFrequencyFromNote();
            }
        });

        octaveUp.setOnClick([this]() {
            if (!useCustomFreq && octave < 8) {
                octave++;
                updateFrequencyFromNote();
            }
        });

        waveToggle.setOnClick([this]() {
            waveType = (waveType == WaveType::Sine) ? WaveType::Saw : WaveType::Sine;
            waveToggle.setText((waveType == WaveType::Sine) ? "Sine" : "Saw");
            waveToggle.setButtonColor((waveType == WaveType::Sine) ? 0xff444488 : 0xff884444);
            dirty = true;
        });
    }

    void update(float dt) {
        noteDown.update(dt);
        noteUp.update(dt);
        octaveDown.update(dt);
        octaveUp.update(dt);
        waveToggle.update(dt);
        removeButton.update(dt);
        customFreqField.update(dt);

        // Handle Enter key for frequency input
        if (m_context.input->isKeyJustPressed(Engine::KeyCode::KEY_ENTER)) {
            std::string freqText = customFreqField.getText();
            if (!freqText.empty()) {
                try {
                    float freq = std::stof(freqText);
                    if (freq >= 20.0f && freq <= 2000.0f) {
                        customFreq = freq;
                        useCustomFreq = true;
                        dirty = true;
                    }
                } catch (...) {
                    // Invalid input, ignore
                }
            }
        }
    }

    void render() {
        noteDown.render();
        noteUp.render();
        octaveDown.render();
        octaveUp.render();
        waveToggle.render();
        removeButton.render();
        customFreqField.render();

        // Draw current note/frequency display
        std::string display;
        if (useCustomFreq) {
            display = std::to_string(customFreq).substr(0, 6) + " Hz";
        } else {
            display = getNoteName() + " (" + std::to_string(getFrequencyOfOsc()) + ")";
        }
        m_context.renderer2D->drawText(display, 320, yOffset + 45, 0xffffffff);
    }

    void reposition(int newY) {
        yOffset = newY;

        noteDown.setPosition({150, newY + 5});
        noteUp.setPosition({230, newY + 5});
        octaveDown.setPosition({150, newY + 40});
        octaveUp.setPosition({230, newY + 40});
        waveToggle.setPosition({320, newY + 5});
        removeButton.setPosition({520, newY + 5});
        customFreqField.setPosition({400, newY + 5});
    }

    float getFrequencyOfOsc() const {
        if (useCustomFreq) return customFreq;
        return getFrequency(currentNote, octave);
    }

    WaveType getWaveType() const {
        return waveType;
    }

    bool isDirty() const {
        return dirty;
    }

    void cleanOscillator() {
        dirty = false;
    }

private:
    void updateFrequencyFromNote() {
        customFreq = getFrequency(currentNote, octave);
        useCustomFreq = false;
        dirty = true;
    }

    std::string getNoteName() const {
        const char* names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        return std::string(names[static_cast<int>(currentNote)]) + std::to_string(octave);
    }
};



// struct OscillatorControl {
    //     Slider<float> freqSlider;
    //     DragField<float> freqDrag;
    //     // Note selection buttons
    //     Button noteDown;
    //     Button noteUp;
    //     Button waveToggle;
    //     Button removeButton;
    //     TextField customFreqField;
    //
    //     Note currentNote = Note::C;
    //     int octave = 4;
    //     WaveType waveType = WaveType::Sine;
    //     bool useCustomFreq = false;
    //     float customFreq = 261.63f; // Middle C
    //     int yOffset;
    //
    //     bool dirty = false;
    //
    //     Engine::EngineContext m_context;
    //
    //     OscillatorControl(Engine::EngineContext& context, Engine::GameContainer& container, int y)
    //         : yOffset(y),
    //           m_context(context),
    //           freqSlider(context, container, SliderConfigWithStepSize<float>{
    //               .pos = {150, y + 5},
    //               .size = {250, 30},
    //               .sliderWidth = 15,
    //               .backgroundColor = 0xff333333,
    //               .sliderColor = 0xff6666aa,
    //               .from = 20.0f,
    //               .to = 2000.0f,
    //               .stepSize = 1.0f
    //           }),
    //           freqDrag(context, container, DragFieldConfig<float>{
    //               .pos = {420, y + 5},
    //               .size = {80, 30},
    //               .backgroundColor = 0xff333333,
    //               .textColor = 0xffffffff,
    //               .from = 20.0f,
    //               .to = 2000.0f,
    //               .stepSize = 0.1f
    //           }),
    //           noteDown(context, container, {
    //               .pos = {150, y + 40},
    //               .padding = {5, 5},
    //               .buttonColor = 0xff444444,
    //               .textColor = 0xffffffff,
    //               .filled = true,
    //               .text = "< Note"
    //           }),
    //           noteUp(context, container, {
    //               .pos = {230, y + 40},
    //               .padding = {5, 5},
    //               .buttonColor = 0xff444444,
    //               .textColor = 0xffffffff,
    //               .filled = true,
    //               .text = "Note >"
    //           }),
    //           waveToggle(context, container, {
    //               .pos = {320, y + 40},
    //               .padding = {5, 5},
    //               .buttonColor = 0xff444488,
    //               .textColor = 0xffffffff,
    //               .filled = true,
    //               .text = "Sine"
    //           }),
    //           removeButton(context, container, {
    //               .pos = {520, y + 5},
    //               .padding = {5, 5},
    //               .buttonColor = 0xff882222,
    //               .textColor = 0xffffffff,
    //               .filled = true,
    //               .text = "X"
    //           }),
    //           customFreqField(context, container, TextFieldConfig{
    //           .pos = {520, y + 40},
    //           .size = {100, 25},
    //           .fillTextField = true,
    //           .backgroundColor = 0xff333333,
    //           .textColor = 0xff00ff00,
    //           .renderInputPrompt = true,
    //           .inputPrompt = "Hz: ",
    //           .maxCharacters = 7
    //           }) {
    //
    //         // Set initial frequency
    //         freqSlider.setValue(261.63f); // Middle C
    //         freqDrag.setValue(261.63f);
    //
    //         // Button callbacks
    //         noteDown.setOnClick([this]() {
    //             if (!useCustomFreq) {
    //                 if (currentNote == Note::C) {
    //                     currentNote = Note::B;
    //                     octave--;
    //                 } else {
    //                     currentNote = static_cast<Note>(static_cast<int>(currentNote) - 1);
    //                 }
    //                 updateFrequency();
    //                 dirty = true;
    //             }
    //         });
    //
    //         noteUp.setOnClick([this]() {
    //             if (!useCustomFreq) {
    //                 if (currentNote == Note::B) {
    //                     currentNote = Note::C;
    //                     octave++;
    //                 } else {
    //                     currentNote = static_cast<Note>(static_cast<int>(currentNote) + 1);
    //                 }
    //                 updateFrequency();
    //                 dirty = true;
    //             }
    //         });
    //
    //         waveToggle.setOnClick([this]() {
    //             waveType = (waveType == WaveType::Sine) ? WaveType::Saw : WaveType::Sine;
    //             waveToggle.setText((waveType == WaveType::Sine) ? "Sine" : "Saw");
    //             waveToggle.setButtonColor((waveType == WaveType::Sine) ? 0xff444488 : 0xff884444);
    //             dirty = true;
    //         });
    //
    //         customFreqField.registerCallback();
    //     }
    //
    //     void update(float dt) {
    //         freqSlider.update(dt);
    //         freqDrag.update(dt);
    //         noteDown.update(dt);
    //         noteUp.update(dt);
    //         waveToggle.update(dt);
    //         removeButton.update(dt);
    //         customFreqField.update(dt);
    //
    //         // Sync frequency displays if slider/drag changed
    //         float sliderVal = freqSlider.getCurrentValue();
    //         float dragVal = freqDrag.getCurrentValue();
    //
    //         if (sliderVal != customFreq || dragVal != customFreq) {
    //             customFreq = sliderVal;
    //             useCustomFreq = true;
    //             dirty = true;
    //         }
    //     }
    //
    //     void render() {
    //         freqSlider.render();
    //         freqDrag.render();
    //         noteDown.render();
    //         noteUp.render();
    //         waveToggle.render();
    //         removeButton.render();
    //         customFreqField.render();
    //
    //         // Draw current note display
    //         // m_context.renderer2D->drawText(getNoteName(), 180, yOffset + 45, 0xffffffff);
    //
    //         if (m_context.input->isKeyJustPressed(Engine::KeyCode::KEY_ENTER)) {
    //             // Get the text from the field - you'll need to add a getter to TextField
    //             std::string freqText = customFreqField.getText();
    //             if (!freqText.empty()) {
    //                 try {
    //                     float freq = std::stof(freqText);
    //                     if (freq >= 20.0f && freq <= 2000.0f) {
    //                         customFreq = freq;
    //                         useCustomFreq = true;
    //                         freqSlider.setValue(customFreq);
    //                         freqDrag.setValue(customFreq);
    //                         dirty = true;
    //                     }
    //                 } catch (...) {
    //                     // Invalid input, ignore
    //                 }
    //             }
    //         }
    //
    //         // Sync frequency displays if slider/drag changed
    //         float sliderVal = freqSlider.getCurrentValue();
    //         float dragVal = freqDrag.getCurrentValue();
    //
    //         if (std::abs(sliderVal - customFreq) > 0.01f || std::abs(dragVal - customFreq) > 0.01f) {
    //             customFreq = sliderVal;
    //             useCustomFreq = true;
    //             dirty = true;
    //         }
    //     }
    //
    //     float getFrequencyOfOsc() const {
    //         if (useCustomFreq) return customFreq;
    //         return calculateNoteFrequency(currentNote, octave);
    //     }
    //
    //     WaveType getWaveType() const {
    //         return waveType;
    //     }
    //
    //     bool isDirty() {
    //         return dirty;
    //     }
    //     void cleanOscillator() {
    //         dirty = false;
    //     }
    // private:
    //     void updateFrequency() {
    //         float freq = calculateNoteFrequency(currentNote, octave);
    //         customFreq = freq;
    //         freqSlider.setValue(freq);
    //         freqDrag.setValue(freq);
    //     }
    //
    //     float calculateNoteFrequency(Note note, int octave) const {
    //         // const float baseFreqs[] = {
    //         //     16.35f, 17.32f, 18.35f, 19.45f, 20.60f, 21.83f,
    //         //     23.12f, 24.50f, 25.96f, 27.50f, 29.14f, 30.87f
    //         // };
    //         // float baseFreq = baseFreqs[static_cast<int>(note)];
    //         // return baseFreq * std::pow(2.0f, octave);
    //         return getFrequency(note,octave);
    //     }
    //
    //     std::string getNoteName() const {
    //         const char* names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    //         return std::string(names[static_cast<int>(currentNote)]) + std::to_string(octave);
    //     }
    // };
