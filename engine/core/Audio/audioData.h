//
// Created by augus on 03.04.2026.
//

#ifndef INC_3DENGINE_AUDIODATA_H
#define INC_3DENGINE_AUDIODATA_H
#pragma once
#include <cstdint>
#include <vector>

#endif //INC_3DENGINE_AUDIODATA_H

struct AudioData {
    std::vector<float> samples;
    uint32_t numChannels;
    uint32_t sampleRate;
    uint32_t bitsPerSample;
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