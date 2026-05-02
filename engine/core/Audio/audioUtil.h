//
// Created by augus on 02.05.2026.
//

#ifndef INC_3DENGINE_AUDIOUTIL_H
#define INC_3DENGINE_AUDIOUTIL_H
#include "audioData.h"

#endif //INC_3DENGINE_AUDIOUTIL_H

inline AudioData mix(const std::vector<AudioData>& signals) {
    if (signals.empty()) return AudioData{};

    AudioData result = signals[0];
    result.samples.assign(result.samples.size(), 0.0f);

    for (const auto& signal : signals) {
        for (size_t i = 0; i < signal.samples.size() && i < result.samples.size(); ++i) {
            result.samples[i] += signal.samples[i];
        }
    }

    float maxPeak = 0.0f;
    for (const auto& sample : result.samples) {
        maxPeak = std::max(maxPeak, std::abs(sample));
    }

    if (maxPeak > 0.95f) {
        float gain = 0.95f / maxPeak;
        for (auto& sample : result.samples) {
            sample *= gain;
        }
    }

    return result;
}