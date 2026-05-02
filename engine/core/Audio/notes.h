//
// Created by augus on 30.04.2026.
//

#ifndef INC_3DENGINE_NOTES_H
#define INC_3DENGINE_NOTES_H
#include <cmath>

#endif //INC_3DENGINE_NOTES_H
#pragma once

constexpr float a4freq = 440.0f;
constexpr int a4Index = 9;

enum class Note {
    C, Cs, D, DS, E, F, Fs, G, Gs, A, As, B
};

inline float getFrequency(Note note, const int octave = 4) {
    int halfSteps = (static_cast<int>(note) - a4Index) + (octave - 4) * 12;
    return a4freq * powf(2.0f, static_cast<float>(halfSteps) / 12.0f);
}