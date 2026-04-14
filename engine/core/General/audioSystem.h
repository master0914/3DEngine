//
// Created by augus on 14.04.2026.
//

#ifndef INC_3DENGINE_AUDIOSYSTEM_H
#define INC_3DENGINE_AUDIOSYSTEM_H


#pragma once
#include <iostream>
#include <SDL_audio.h>
#include <unordered_map>

#include "SDL.h"
#include "../Audio/audioData.h"

namespace Engine {

struct AudioClip {
    AudioData data;
    double playhead = 0;  // aktuelle position in samples
    bool playing = false;
    bool loop = false;
    float volume = 1.0f;
    double resampleRatio = 1.0; // sourceRate / targetRate
};

class AudioSystem {
public:
    AudioSystem() = default;
    ~AudioSystem() { shutdown(); }

    bool init() {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
            std::cerr << "SDL Audio init failed: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_AudioSpec desired{};
        desired.freq     = 44100;
        desired.format   = AUDIO_F32SYS;
        desired.channels = 2;
        desired.samples  = 512;
        desired.callback = audioCallback;
        desired.userdata = this;

        m_deviceId = SDL_OpenAudioDevice(nullptr, 0, &desired, &m_spec, 0);
        if (m_deviceId == 0) {
            std::cerr << "SDL_OpenAudioDevice failed: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_PauseAudioDevice(m_deviceId, 0); // starten
        return true;
    }

    void shutdown() {
        if (m_deviceId != 0) {
            SDL_CloseAudioDevice(m_deviceId);
            m_deviceId = 0;
        }
    }

    // gibt handle zurück zum späteren stoppen/pausieren
    int play(const AudioData& data, bool loop = false, float volume = 1.0f) {
        SDL_LockAudioDevice(m_deviceId);
        int id = m_nextId++;
        double resampleRatio = static_cast<double>(data.sampleRate) / m_spec.freq;
        m_clips[id] = AudioClip{data, 0.0, true, loop, volume, resampleRatio};
        SDL_UnlockAudioDevice(m_deviceId);
        return id;
    }

    void stop(int id) {
        SDL_LockAudioDevice(m_deviceId);
        m_clips.erase(id);
        SDL_UnlockAudioDevice(m_deviceId);
    }

    void setVolume(int id, float volume) {
        SDL_LockAudioDevice(m_deviceId);
        if (m_clips.count(id)) m_clips[id].volume = volume;
        SDL_UnlockAudioDevice(m_deviceId);
    }

private:
    SDL_AudioDeviceID m_deviceId = 0;
    SDL_AudioSpec m_spec{};
    std::unordered_map<int, AudioClip> m_clips;
    int m_nextId = 0;

    static void audioCallback(void* userdata, uint8_t* stream, int len) {
        auto* self = static_cast<AudioSystem*>(userdata);
        auto* output = reinterpret_cast<float*>(stream);
        int numFrames = len / sizeof(float);

        std::fill(output, output + numFrames, 0.0f);

        for (auto& [id, clip] : self->m_clips) {
            if (!clip.playing) continue;

            for (int i = 0; i < numFrames; i++) {
                if (clip.playhead >= clip.data.samples.size()) {
                    if (clip.loop) clip.playhead = 0;
                    else { clip.playing = false; break; }
                }
                output[i] += clip.data.samples[clip.playhead++] * clip.volume;
            }
        }
    }
};
}


#endif //INC_3DENGINE_AUDIOSYSTEM_H