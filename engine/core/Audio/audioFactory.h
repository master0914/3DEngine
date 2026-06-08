//
// Created by augus on 30.04.2026.
//





#ifndef INC_3DENGINE_AUDIOFACTORY_H
#define INC_3DENGINE_AUDIOFACTORY_H
#include <cmath>
#include <complex>
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

    float adjustDurationForExactCycles(float frequencyHz, float desiredDurationSeconds, uint32_t sampleRate) {
        if (frequencyHz <= 0.0f || sampleRate == 0) {
            return desiredDurationSeconds;
        }
        float periodSeconds = 1.0f / frequencyHz;
        float samplesPerCycle = periodSeconds * static_cast<float>(sampleRate);
        float totalSamplesDesired = desiredDurationSeconds * static_cast<float>(sampleRate);
        float numCycles = totalSamplesDesired / samplesPerCycle;
        float numCompleteCycles = std::round(numCycles);
        if (numCompleteCycles < 1.0f) {
            numCompleteCycles = 1.0f;
        }
        float adjustedDurationSeconds = (numCompleteCycles * samplesPerCycle) / static_cast<float>(sampleRate);
        return adjustedDurationSeconds;
    }
    size_t getSampleSizeForExactCycles(float frequencyHz, float desiredDurationSeconds, uint32_t sampleRate, uint32_t numChannels) {
        float duration = adjustDurationForExactCycles(frequencyHz, desiredDurationSeconds, sampleRate);
        return static_cast<size_t>(duration * static_cast<float>(sampleRate) * static_cast<float>(numChannels));
    }

    // NORMAL SINE
    AudioData generateSine(float frequencyHz, float durationSeconds) {
        AudioData result = defaultConfig;

        // auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        auto requiredSize = getSampleSizeForExactCycles(frequencyHz, durationSeconds, result.sampleRate, result.numChannels);


        result.samples.resize(requiredSize);
        fillSine(result, frequencyHz);
        return result;
    }

    AudioData generateSine(uint32_t numChannels, uint32_t sampleRate, float frequencyHz, float durationSeconds) {
        AudioData result;
        result.numChannels = numChannels;
        result.sampleRate = sampleRate;
        result.bitsPerSample = 32;  // Float ist Standard
        // auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        auto requiredSize = getSampleSizeForExactCycles(frequencyHz, durationSeconds, result.sampleRate, result.numChannels);
        result.samples.resize(requiredSize);
        fillSine(result, frequencyHz);
        return result;
    }

    // erstellt das selbe signal auf allen channels
    void fillSine(AudioData& audio, float frequency) { // NOLINT(*-convert-member-functions-to-static)
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

    // NORMAL SAW
    AudioData generateSaw(float frequencyHz, float durationSeconds){
        AudioData result = defaultConfig;
        // auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        auto requiredSize = getSampleSizeForExactCycles(frequencyHz, durationSeconds, result.sampleRate, result.numChannels);
        result.samples.resize(requiredSize);
        fillSaw(result, frequencyHz);
        return result;
    }

    AudioData generateSaw(uint32_t numChannels, uint32_t sampleRate, float frequencyHz, float durationSeconds) {
        AudioData result;
        result.numChannels = numChannels;
        result.sampleRate = sampleRate;
        result.bitsPerSample = 32;  // Float ist Standard
        // auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        auto requiredSize = getSampleSizeForExactCycles(frequencyHz, durationSeconds, result.sampleRate, result.numChannels);
        result.samples.resize(requiredSize);
        fillSaw(result, frequencyHz);
        return result;
    }

    void fillSaw(AudioData& audio, float frequency) {// NOLINT(*-convert-member-functions-to-static)
        const float invSampleRate = 1.0f / audio.sampleRate; // NOLINT(*-narrowing-conversions)
        float phase = 0.0f;
        const float phaseIncrement = frequency * invSampleRate;

        for (size_t i = 0; i < (audio.samples.size() / audio.numChannels); i++) {
            float value = 2.0f * phase - 1.0f;

            phase += phaseIncrement;
            if (phase >= 1.0f) {
                phase -= 1.0f;
            }

            for (uint32_t ch = 0; ch < audio.numChannels; ch++) {
                audio.samples[i * audio.numChannels + ch] = value;
            }
        }
    }

    // BANDLIMITED SAW
    AudioData generateSawBandlimited(float frequencyHz, float durationSeconds){
        AudioData result = defaultConfig;
        // auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        auto requiredSize = getSampleSizeForExactCycles(frequencyHz, durationSeconds, result.sampleRate, result.numChannels);
        result.samples.resize(requiredSize);
        fillSawBandlimited(result, frequencyHz);
        return result;
    }

    AudioData generateSawBandlimited(uint32_t numChannels, uint32_t sampleRate, float frequencyHz, float durationSeconds) {
        AudioData result;
        result.numChannels = numChannels;
        result.sampleRate = sampleRate;
        result.bitsPerSample = 32;  // Float ist Standard
        // auto requiredSize = static_cast<size_t>(durationSeconds * static_cast<float>(result.sampleRate) * static_cast<float>(result.numChannels));
        auto requiredSize = getSampleSizeForExactCycles(frequencyHz, durationSeconds, result.sampleRate, result.numChannels);
        result.samples.resize(requiredSize);
        fillSawBandlimited(result, frequencyHz);
        return result;
    }

    void fillSawBandlimited(AudioData& audio, float frequency) {// NOLINT(*-convert-member-functions-to-static)
        const float invSampleRate = 1.0f / audio.sampleRate; // NOLINT(*-narrowing-conversions)
        float phase = 0.0f;
        const float phaseIncrement = frequency * invSampleRate;

        // Nyquist-Frequenz
        const float nyquist = audio.sampleRate / 2.0f; // NOLINT(*-narrowing-conversions)

        // Anzahl der Harmonischen unter Nyquist
        const int numHarmonics = static_cast<int>(nyquist / frequency);

        for (size_t i = 0; i < (audio.samples.size() / audio.numChannels); i++) {
            float value = 0.0f;

            // Additive Synthese nur mit Harmonischen unter Nyquist
            for (int h = 1; h <= numHarmonics; h++) {
                value += std::sin(2.0f * M_PI * h * phase) / h; // NOLINT(*-narrowing-conversions)
            }

            value = -2.0f / M_PI * value; // NOLINT(*-narrowing-conversions)

            phase += phaseIncrement;
            if (phase >= 1.0f) {
                phase -= 1.0f;
            }

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
