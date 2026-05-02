//
// Created by augus on 14.04.2026.
//

#ifndef INC_3DENGINE_AUDIOTEST_H
#define INC_3DENGINE_AUDIOTEST_H
#pragma once

#include "IGame.h"
#include "../../engine/core/Audio/waveformGenerator.h"
#include "../../engine/core/Audio/wavLoader.h"
#include "vector.h"
#include "../../engine/core/Audio/audioFactory.h"
#include "../../engine/core/Audio/audioUtil.h"
#include "../../engine/core/Audio/notes.h"

#endif //INC_3DENGINE_AUDIOTEST_H

inline void testWavLoading() {

}

class TestAudioGame: public Engine::IGame{
public:
    explicit TestAudioGame(Engine::EngineContext& context, Engine::GameContainer& container) :
    IGame(context,container),
    // clip(wavLoad("C:/Users/augus/CLionProjects/3DEngine/engine/core/Audio/AudioTest/Utopia Critical Stop.WAV")),
    audioFactory(),
    clip(generateCustomClip())
    {
        // clip = wavLoad("C:/Users/augus/CLionProjects/3DEngine/engine/core/Audio/AudioTest/Utopia Critical Stop.WAV");
        wavForm = generateWaveformBars(clip);
        imgID = m_context.renderer2D->loadImage(wavForm);

    }
    void update(float dt) override{
        if (m_context.input->isKeyJustPressed(Engine::KeyCode::KEY_Q)) {
            playClip();
        }
    }
    void render() override{
        m_context.renderer2D->fillRectangle(0,0,m_context.window->getm_Height(),m_context.window->getm_Width(), 0xff111111);

        // wavForm of mainclip
        m_context.renderer2D->drawImage(imgID,0,0);

        // debug view
        m_context.renderer2D->drawImage(d1ID,0,200);
        m_context.renderer2D->drawImage(d2ID,0,400);
        m_context.renderer2D->drawImage(d3ID,0,600);
        m_context.renderer2D->drawImage(clipDebugID,0,800);

        m_context.renderer2D->present();
    }
    void onInit() override{}
    void onExit() override{}
    void handleInput(float dt);
    void playClip() {
        m_context.audio->play(clip);
    }
private:
    AudioFactory audioFactory{};
    AudioData clip;
    Engine::Image wavForm;
    Engine::Image clipDebug;
    int clipDebugID;
    int imgID;

    Engine::Image debug1;
    Engine::Image debug2;
    Engine::Image debug3;
    int d1ID,d2ID,d3ID;

    AudioData generateCustomClip() {
        float freqC = getFrequency(Note::C);
        float freqE = getFrequency(Note::C,5);
        float freqG = getFrequency(Note::G);
        LOG_INFO(freqC);
        LOG_INFO(freqE);
        LOG_INFO(freqG);
        AudioData clip1 = audioFactory.generateSine(freqC,3.0f);
        AudioData clip2 = audioFactory.generateSine(freqE,3.0f);
        AudioData clip3 = audioFactory.generateSine(freqG,3.0f);
        // debug view setup
        debug1 = debugWaveFormView(clip1,0,0.01f);
        debug2 = debugWaveFormView(clip2,0,0.01f);
        debug3 = debugWaveFormView(clip3,0,0.01f);
        d1ID = m_context.renderer2D->loadImage(debug1);
        d2ID = m_context.renderer2D->loadImage(debug2);
        d3ID = m_context.renderer2D->loadImage(debug3);

        AudioData finalClip = mix({clip1,clip2,clip3});
        // AudioData finalClip;
        // finalClip.sampleRate = 44100;
        // finalClip.samples.resize(clip1.samples.size(), 0.0f);
        //
        // for (size_t i = 0; i < clip1.samples.size(); i++) {
        //     finalClip.samples[i] = clip1.samples[i] + clip2.samples[i] + clip3.samples[i];
        // }

        clipDebug = debugWaveFormView(finalClip, 0,0.01f);
        clipDebugID = m_context.renderer2D->loadImage(clipDebug);

        return finalClip;

    }
};