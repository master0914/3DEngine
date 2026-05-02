//
// Created by augus on 14.04.2026.
//

#ifndef INC_3DENGINE_WAVEFORMGENERATOR_H
#define INC_3DENGINE_WAVEFORMGENERATOR_H
#include "audioData.h"
#include "../General/image.h"
#include "../util/Logger.h"

#endif //INC_3DENGINE_WAVEFORMGENERATOR_H

inline Engine::Image generateWaveform(const AudioData& audio,
                                        int targetWidth = 800,
                                        int targetHeight = 200,
                                        uint32_t wavColor = 0xff0033dd,
                                        uint32_t backgroundColor = 0x00000000,
                                        uint32_t centerlineColor = 0xff404040){
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
        if (static_cast<size_t>(startSample) >= audio.samples.size()) break;

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
                                        uint32_t backgroundColor = 0x00000000) {
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

// vielen dank an deepseek:
inline Engine::Image debugWaveFormView(const AudioData& audio,
                                        float viewWindowStartTime,
                                        float viewWindowSize,
                                        int targetWidth = 800,
                                        int targetHeight = 200,
                                        uint32_t waveColor = 0xff00ff00,
                                        uint32_t pointColor = 0xffff0000,
                                        uint32_t backgroundColor = 0x00000000,
                                        uint32_t gridColor = 0xff333333) {

    if (audio.samples.empty() || audio.sampleRate == 0) {
        return {targetWidth, targetHeight, backgroundColor};
    }

    std::vector<uint32_t> pixels(targetWidth * targetHeight, backgroundColor);

    // Berechne Sample-Index Bereich
    auto startSample = static_cast<size_t>(viewWindowStartTime * audio.sampleRate);
    auto endSample = static_cast<size_t>((viewWindowStartTime + viewWindowSize) * audio.sampleRate);

    // Begrenze auf verfügbare Samples
    startSample = std::min(startSample, audio.samples.size() - 1);
    endSample = std::min(endSample, audio.samples.size());

    size_t numSamples = endSample - startSample;
    if (numSamples == 0) return {targetWidth, targetHeight, backgroundColor};

    float halfHeight = targetHeight / 2.0f;
    float centerY = halfHeight;

    // Gitter zeichnen (Hilfslinien)
    // Horizontale Linien bei -1, -0.5, 0, 0.5, 1
    for (float level = -1.0f; level <= 1.0f; level += 0.5f) {
        int y = static_cast<int>(centerY - level * halfHeight);
        y = std::clamp(y, 0, targetHeight - 1);
        for (int x = 0; x < targetWidth; x++) {
            pixels[y * targetWidth + x] = gridColor;
        }

    }

    // Vertikale Linien für Zeitmarkierungen
    int numVerticalLines = std::min(10, (int)viewWindowSize);
    for (int i = 0; i <= numVerticalLines; i++) {
        float time = viewWindowStartTime + (viewWindowSize * i / numVerticalLines);
        float xFloat = (i / (float)numVerticalLines) * targetWidth;
        int x = static_cast<int>(xFloat);

        if (x >= 0 && x < targetWidth) {
            for (int y = 0; y < targetHeight; y++) {
                pixels[y * targetWidth + x] = gridColor;
            }
        }
    }

    // Wenn zu viele Samples, nur jeden n-ten Punkt zeichnen
    int step = 1;
    if (numSamples > targetWidth * 2) {
        step = numSamples / (targetWidth * 2);
    }

    // Punkte und Linien zeichnen
    std::vector<std::pair<int, int>> points;

    for (size_t i = 0; i < numSamples; i += step) {
        size_t sampleIndex = startSample + i;
        if (sampleIndex >= audio.samples.size()) break;

        float sample = audio.samples[sampleIndex];
        float timeOffset = (float)i / (float)audio.sampleRate;

        // X-Position basierend auf Zeit
        int x = static_cast<int>((timeOffset / viewWindowSize) * targetWidth);
        if (x < 0 || x >= targetWidth) continue;

        // Y-Position basierend auf Sample-Wert (-1..1)
        int y = static_cast<int>(centerY - sample * halfHeight);
        y = std::clamp(y, 0, targetHeight - 1);

        points.emplace_back(x, y);

        // Punkt zeichnen
        if (x >= 0 && x < targetWidth && y >= 0 && y < targetHeight) {
            pixels[y * targetWidth + x] = pointColor;
        }
    }

    // Linien zwischen Punkten zeichnen (DDA Algorithmus)
    for (size_t i = 1; i < points.size(); i++) {
        int x0 = points[i-1].first;
        int y0 = points[i-1].second;
        int x1 = points[i].first;
        int y1 = points[i].second;

        // Bresenham's line algorithm
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx - dy;

        int x = x0, y = y0;
        while (true) {
            if (x >= 0 && x < targetWidth && y >= 0 && y < targetHeight) {
                pixels[y * targetWidth + x] = waveColor;
            }
            if (x == x1 && y == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x += sx; }
            if (e2 < dx) { err += dx; y += sy; }
        }
    }

    // Zeitbeschriftungen (optional - sehr einfache Text-Darstellung)
    // Nur horizontale Linien mit Labels simulieren
    for (int i = 0; i <= numVerticalLines; i++) {
        float time = viewWindowStartTime + (viewWindowSize * i / numVerticalLines);
        int x = static_cast<int>((i / (float)numVerticalLines) * targetWidth);

        // Kleine Markierung
        if (x >= 0 && x < targetWidth) {
            for (int offY = -5; offY <= 5; offY++) {
                int y = centerY + offY;
                if (y >= 0 && y < targetHeight) {
                    pixels[y * targetWidth + x] = 0xffffffff;
                }
            }
        }
    }

    return {targetWidth, targetHeight, std::move(pixels)};
}