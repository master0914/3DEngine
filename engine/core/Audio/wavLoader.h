//
// Created by augus on 03.04.2026.
//

#ifndef INC_3DENGINE_WAVLOADER_H
#define INC_3DENGINE_WAVLOADER_H
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <iostream>

#include "audioData.h"

#endif //INC_3DENGINE_WAVLOADER_H

inline bool readChunk(std::ifstream& file, char* id, uint32_t& size) {
    file.read(id,4);
    file.read(reinterpret_cast<char*>(&size),sizeof(size)); // anscheinend ist der cast zum char* wichtig, da sonst fehler passieren XD ka wieso
    return file.good();
}

inline AudioData wavLoad(const std::string& filename) {
    AudioData result;
    std::ifstream file(filename, std::ios::binary);  // datei binär lesen, nicht mit text

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        // ReSharper disable once CppSomeObjectMembersMightNotBeInitialized
        return result;
    }

    char riffHeader[4];
    uint32_t fileSize;
    if (!readChunk(file,riffHeader,fileSize) || std::string(riffHeader,4) != "RIFF") { // weiß nicht ob das funktioniert, weil für (riffHeader != "RIFF") zuerst readChunk ausgeführt werden muss
        std::cerr << "Could not read riff header" << std::endl;
        // ReSharper disable once CppSomeObjectMembersMightNotBeInitialized
        return result;
    }

    char waveFormat[4];
    file.read(waveFormat,4);
    if (std::string(waveFormat,4) != "WAVE") {
        std::cerr << "Could not read wave format" << std::endl;
        // ReSharper disable once CppSomeObjectMembersMightNotBeInitialized
        return result;
    }

    uint32_t dataSize = 0;
    std::vector<char> rawData;
    bool fmtFound = false;
    bool dataFound = false;

    while (!dataFound && file.good()) {
        char chunkID[4];
        uint32_t chunkSize;
        if (!readChunk(file,chunkID,chunkSize)) {
            std::cerr << "Could not read data chunk" << std::endl;
            return result;
        }
        // look for fmt
        if (std::string(chunkID,4) != "fmt ") {
            if (chunkSize < 16) {
                std::cerr << "Incorrect fmt chunk(too small)" << std::endl;
                return result;
            }
            uint16_t audioFormat;
            file.read(reinterpret_cast<char*>(&audioFormat), 2);
            file.read(reinterpret_cast<char*>(&result.numChannels), 2);
            file.read(reinterpret_cast<char*>(&result.sampleRate), 4);

            uint32_t byteRate;
            uint16_t blockAlign;
            file.read(reinterpret_cast<char*>(&byteRate), 4);
            file.read(reinterpret_cast<char*>(&blockAlign), 2);
            file.read(reinterpret_cast<char*>(&result.bitsPerSample), 2);
            fmtFound = true;
        }
        else if (std::string(chunkID,4) == "data") {
            dataSize = chunkSize;
            rawData.resize(dataSize);
            file.read(rawData.data(),dataSize);
            dataFound = true;
        }
        else {
            // hier wird der chunk übersprungen da es sich nicht um fmt oder data handelt und neu gesucht
            file.seekg(chunkSize,std::ios::cur);
        }
    }

    if (!fmtFound || !dataFound || rawData.empty()) {
        std::cerr << "No fmt or data found" << std::endl;
        return result;
    }

    // write to result/convert to float [0|1]
    size_t totalSamples = dataSize / (result.bitsPerSample / 8);
    result.samples.resize(totalSamples);
    const auto bytePtr = reinterpret_cast<const uint8_t*>(rawData.data());

    for (size_t i = 0; i < totalSamples; i++) {
        float sample = 0.0f;
        // danke an deepseek für die conversion formeln
        if (result.bitsPerSample == 8) {
            const uint8_t val = bytePtr[i];
            sample = (val - 128.0f) / 128.0f; // NOLINT(*-narrowing-conversions)
        }
        else if (result.bitsPerSample == 16) {
            const int16_t val = *reinterpret_cast<const int16_t*>(bytePtr + i * 2);
            sample = val / 32768.0f; // NOLINT(*-narrowing-conversions)
        }
        else if (result.bitsPerSample == 24) {
            int32_t val = 0;
            val |= bytePtr[i*3];
            val |= bytePtr[i*3+1] << 8;
            val |= bytePtr[i*3+2] << 16;
            if (val & 0x800000) {
                val |= 0xFF000000; // NOLINT(*-narrowing-conversions)
            }
            sample = val / 8388608.0f; // NOLINT(*-narrowing-conversions)
        }
        else if (result.bitsPerSample == 32) {
            const int32_t val = *reinterpret_cast<const int32_t*>(bytePtr + i * 4);
            sample = val / 2147483648.0f; // NOLINT(*-narrowing-conversions)
        }
        else {
            std::cerr << "sampleformat not supported" << result.bitsPerSample << std::endl;
            return result;
        }
        result.samples[i] = sample;
    }

    // debug ausgabe
    std::cout << "Datei erfolgreich geladen: " << filename << std::endl;
    std::cout << "  Kanäle: " << result.numChannels << std::endl;
    std::cout << "  Sample-Rate: " << result.sampleRate << " Hz" << std::endl;
    std::cout << "  Bittiefe: " << result.bitsPerSample << " Bit" << std::endl;
    std::cout << "  Samples (gesamt): " << totalSamples << std::endl;
    std::cout << "  Dauer: " << (float)totalSamples / result.sampleRate / result.numChannels << " s" << std::endl;

    return result;
}