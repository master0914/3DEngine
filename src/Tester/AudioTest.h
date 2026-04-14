//
// Created by augus on 14.04.2026.
//

#ifndef INC_3DENGINE_AUDIOTEST_H
#define INC_3DENGINE_AUDIOTEST_H
#pragma once

#include "IGame.h"
#include "../../engine/core/Audio/waveformGenerator.h"
#include "../../engine/core/Audio/wavLoader.h"

#endif //INC_3DENGINE_AUDIOTEST_H

inline void testWavLoading() {

}

class TestAudioGame: public Engine::IGame{
public:
    explicit TestAudioGame(Engine::EngineContext& context, Engine::GameContainer& container) :
    IGame(context,container),
    // clip(wavLoad("C:/Users/augus/CLionProjects/3DEngine/engine/core/Audio/AudioTest/Utopia Critical Stop.WAV")),
    clip(wavLoad("C:/Users/augus/CLionProjects/3DEngine/engine/core/Audio/AudioTest/Haaalo.wav")),
    
    wavForm(generateWaveformBars(clip))
    {
        // clip = wavLoad("C:/Users/augus/CLionProjects/3DEngine/engine/core/Audio/AudioTest/Utopia Critical Stop.WAV");
        // wavForm = generateWaveform(clip);
        imgID = m_context.renderer2D->loadImage(wavForm);
    }
    void update(float dt) override{
        if (m_context.input->isKeyJustPressed(Engine::KeyCode::KEY_Q)) {
            playClip();
        }
    }
    void render() override{
        m_context.renderer2D->drawImage(imgID,0,0);
        m_context.renderer2D->present();
    }
    void onInit() override{}
    void onExit() override{}
    void handleInput(float dt);
    void playClip() {
        m_context.audio->play(clip);
    }
private:
    AudioData clip;
    Engine::Image wavForm;
    int imgID;
};