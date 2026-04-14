//
// Created by augus on 14.04.2026.
//

#ifndef INC_3DENGINE_WAVEFORMGENERATOR_H
#define INC_3DENGINE_WAVEFORMGENERATOR_H
#include "audioData.h"
#include "../General/image.h"
#include "../util/Logger.h"

#endif //INC_3DENGINE_WAVEFORMGENERATOR_H

inline Engine::Image generateWaveform(const AudioData& audio, int targetWidth = 800, int targetHeight = 200, uint32_t wavColor = 0xff0033dd, uint32_t backgroundColor = 0xff000000, uint32_t centerlineColor = 0xff404040) {
    std::vector<uint32_t> pixels(targetWidth * targetHeight, backgroundColor);
    if (audio.samples.empty()) {
        LOG_WARN("Tried to generateWaveform of an empty Sample");
        return {targetWidth,targetHeight,pixels};
    }

    int samplesPerPixel = std::max(1,static_cast<int>(audio.samples.size()) / targetWidth);
    float halfHeight = static_cast<float>(targetHeight) / 2.0f;
    float centerY = halfHeight;

    for (int x = 0; x < targetWidth; x++) {

        int startSample = x * samplesPerPixel;
        int endSample = std::min(static_cast<int>(audio.samples.size()), (x+1) * samplesPerPixel);
        if (startSample >= audio.samples.size()) break;

        float minVal = 0.0f, maxVal = 0.0f;
        for (int i = startSample; i < endSample; i++) {
            float s = audio.samples[i];
            if (s < minVal) minVal = s;
            if (s > maxVal) maxVal = s;
        }

        int yMin = std::clamp(static_cast<int>(centerY + minVal * halfHeight), 0, targetHeight - 1);
        int yMax = std::clamp(static_cast<int>(centerY + maxVal * halfHeight), 0, targetHeight - 1);

        for (int y = yMin; y <= yMax; y++) {
            pixels[y * targetWidth + x] = wavColor;
        }

        pixels[static_cast<int>(centerY) * targetWidth + x] = centerlineColor;
    }

    return {targetWidth,targetHeight,pixels};
}

inline Engine::Image generateWaveformBars(const AudioData& audio,
                                          int targetWidth = 800,
                                          int targetHeight = 200,
                                          uint32_t barColor = 0xff0033dd,
                                          uint32_t backgroundColor = 0xff000000) {
    std::vector<uint32_t> pixels(targetWidth * targetHeight, backgroundColor);
    if (audio.samples.empty()) return {targetWidth, targetHeight, pixels};

    int samplesPerBar = std::max(1, (int)audio.samples.size() / targetWidth);
    float halfHeight = targetHeight / 2.0f;
    float centerY = halfHeight;

    for (int x = 0; x < targetWidth; x++) {
        int startSample = x * samplesPerBar;
        int endSample = std::min((int)audio.samples.size(), (x + 1) * samplesPerBar);
        if (startSample >= audio.samples.size()) break;

        // Berechne durchschnittliche absolute Amplitude (RMS) für diesen Balken
        float sum = 0.0f;
        for (int i = startSample; i < endSample; i++) {
            sum += std::abs(audio.samples[i]);
        }
        float avgAbs = sum / (endSample - startSample);
        int barHeight = static_cast<int>(avgAbs * halfHeight * 1.5f); // Faktor für bessere Sichtbarkeit
        barHeight = std::min(barHeight, (int)halfHeight);

        // Zeichne symmetrische Balken nach oben und unten
        for (int y = 0; y < barHeight; y++) {
            // Oberer Balken
            int upperY = (int)centerY - y - 1;
            if (upperY >= 0) pixels[upperY * targetWidth + x] = barColor;
            // Unterer Balken
            int lowerY = (int)centerY + y;
            if (lowerY < targetHeight) pixels[lowerY * targetWidth + x] = barColor;
        }
    }
    return {targetWidth, targetHeight, pixels};
}