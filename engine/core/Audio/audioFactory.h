//
// Created by augus on 30.04.2026.
//

#ifndef INC_3DENGINE_AUDIOFACTORY_H
#define INC_3DENGINE_AUDIOFACTORY_H
#include <cmath>
#include <utility>

#include "audioData.h"
#endif //INC_3DENGINE_AUDIOFACTORY_H

#pragma once


class AudioFactory {
public:
    AudioFactory() {
        defaultConfig.numChannels = 1;
        defaultConfig.sampleRate = 44100;
        defaultConfig.bitsPerSample = 32;
        defaultConfig.samples.clear();
    }

    explicit AudioFactory(AudioData audioTemplate)
        : defaultConfig(std::move(audioTemplate)){}

    AudioData generateSine(float frequencyHz, float durationSeconds) {
        AudioData result = defaultConfig;


        // LOG_INFO("SampleRate " << result.sampleRate);
        // LOG_INFO("NumChannels " << result.numChannels);
        // LOG_INFO("Bits Per Sample " << result.bitsPerSample);
        auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        // LOG_INFO("required Size " << requiredSize);


        result.samples.resize(requiredSize);
        fillSine(result, frequencyHz);
        return result;
    }

    AudioData generateSine(uint32_t numChannels, uint32_t sampleRate, float frequencyHz, float durationSeconds) {
        AudioData result;
        result.numChannels = numChannels;
        result.sampleRate = sampleRate;
        result.bitsPerSample = 32;  // Float ist Standard
        auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        result.samples.resize(requiredSize);
        fillSine(result, frequencyHz);
        return result;
    }

    // erstellt das selbe signal auf allen channels
    void fillSine(AudioData& audio, float frequency) {
        const float angularFreq = 2.0f * M_PI * frequency; // NOLINT(*-narrowing-conversions)
        const float invSampleRate = 1.0f / audio.sampleRate; // NOLINT(*-narrowing-conversions)

        for (size_t i = 0; i < (audio.samples.size() / audio.numChannels); i++) {
            float time = i * invSampleRate; // NOLINT(*-narrowing-conversions)
            float value = std::sin(angularFreq * time);

            for (uint32_t ch = 0; ch < audio.numChannels; ch++) {
                audio.samples[i * audio.numChannels + ch] = value;
            }
        }

    }

private:
    AudioData defaultConfig{};
    // {
    //     .samples = {},
    //     .numChannels = 1,
    //     .sampleRate = 44100,
    //     .bitsPerSample = 32
    // };
};
