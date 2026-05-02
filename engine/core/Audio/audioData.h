//
// Created by augus on 03.04.2026.
//

#ifndef INC_3DENGINE_AUDIODATA_H
#define INC_3DENGINE_AUDIODATA_H
#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>

#endif //INC_3DENGINE_AUDIODATA_H

struct AudioData {
    std::vector<float> samples = {};
    uint32_t numChannels = 1;
    uint32_t sampleRate = 44100;
    uint32_t bitsPerSample = 32;

    [[nodiscard]] size_t timeToIndex(float seconds) const {
        return static_cast<size_t>(sampleRate * seconds); // NOLINT(*-narrowing-conversions)
    }

    [[nodiscard]] float duration() const {
        if (numChannels == 0 || sampleRate == 0) return 0.0f;
        return samples.size() / static_cast<float>(numChannels * sampleRate); // NOLINT(*-narrowing-conversions)
    }

    void setVolume(float volume) {
        for (auto& sample : samples) {
            sample *= volume;
        }
    }
    void setVolumeClipped(float volume) {
        for (auto& sample : samples) {
            sample *= volume;
            sample = std::clamp(sample, -1.0f, 1.0f);

        }
    }

    // concatenates the clips
    AudioData operator+(const AudioData& other) const {
        if (sampleRate != other.sampleRate || numChannels != other.numChannels) {
            throw std::runtime_error("Cannot concatenate: Incompatible formats");
        }

        AudioData result;
        result.numChannels = numChannels;
        result.sampleRate = sampleRate;
        result.bitsPerSample = bitsPerSample;

        result.samples.reserve(samples.size() + other.samples.size());
        result.samples.insert(result.samples.end(), samples.begin(), samples.end());
        result.samples.insert(result.samples.end(), other.samples.begin(), other.samples.end());

        return result;
    }
    AudioData& operator+=(const AudioData& other) {
        if (sampleRate != other.sampleRate || numChannels != other.numChannels) {
            throw std::runtime_error("Cannot concatenate: Incompatible formats");
        }

        samples.reserve(samples.size() + other.samples.size());
        samples.insert(samples.end(), other.samples.begin(), other.samples.end());
        return *this;
    }

    // mixes the clips   WICHTIG!!! NICHT KETTEN!!! SONST WIRD DAZWISCHEN NORMALISIERT!!!
    AudioData operator|(const AudioData& other) const {
        if (sampleRate != other.sampleRate || numChannels != other.numChannels) {
            throw std::runtime_error("Cannot mix: Incompatible formats");
        }

        size_t maxSize = std::max(samples.size(), other.samples.size());
        AudioData result = *this;
        result.samples.resize(maxSize, 0.0f);

        for (size_t i = 0; i < other.samples.size(); ++i) {
            result.samples[i] += other.samples[i];
        }

        // Peak normalisation
        float maxPeak = 0.0f;
        for (const auto& sample: result.samples) {
            maxPeak = std::max(maxPeak, std::abs(sample));
        }
        if (maxPeak > 0.95f) {
            float gain = 0.95f / maxPeak;
            for (auto& sample : result.samples) {
                sample *= gain;
            }
        }

        // clipping prot
        // for (auto& sample : result.samples) {
        //     sample = std::clamp(sample, -1.0f, 1.0f);
        // }

        return result;
    }
    AudioData& operator|=(const AudioData& other) {
        if (sampleRate != other.sampleRate || numChannels != other.numChannels) {
            throw std::runtime_error("Cannot mix: Incompatible formats");
        }

        samples.resize(std::max(samples.size(), other.samples.size()), 0.0f);
        for (size_t i = 0; i < other.samples.size(); ++i) {
            samples[i] += other.samples[i];
            // clipping prot
            samples[i] = std::clamp(samples[i], -1.0f, 1.0f);
        }

        return *this;
    }
};

// #pragma pack(push, 1) // braucht man anscheinend um kein padding über 1 Byte zu erschaffen
// struct WaveHeader {
//     char     chunkId[4];          // riff
//     uint32_t chunkSize;           // dateigröße (8bytes)
//     char     format[4];           // wave
//
//     char     subchunk1Id[4];      // "fmt "   (leerzeichen ist wichtig!!!)
//     uint32_t subchunk1Size;       // größe fmtChunk (16 für PCM)
//     uint16_t audioFormat;         // 1 für PCM
//     uint16_t numChannels;         // 1 = mono 2 = stereo
//     uint32_t sampleRate;          // Samplerate (hz)
//     uint32_t byteRate;            // Bytes/s
//     uint16_t blockAlign;          // Bytes/sampleFrame (kanäle * bitsPerSample/8)
//     uint16_t bitsPerSample;       // (8, 16, 24, 32)
//
//     char     subchunk2Id[4];      // "data"
//     uint32_t subchunk2Size;       // größe der daten in bytes
// };
// #pragma pack(pop)