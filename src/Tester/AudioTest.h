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
        m_context.renderer2D->drawImage(d4ID,800,200);
        m_context.renderer2D->drawImage(d5ID,800,400);
        m_context.renderer2D->drawImage(d6ID,800,600);
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
    Engine::Image debug4;
    Engine::Image debug5;
    Engine::Image debug6;
    int d1ID,d2ID,d3ID,d4ID,d5ID,d6ID;

    AudioData generateCustomClip() {
        float freqC = getFrequency(Note::C);
        float freqE = getFrequency(Note::C,5);
        float freqG = getFrequency(Note::G);

        LOG_INFO(freqC);
        LOG_INFO(freqE);
        LOG_INFO(freqG);

        AudioData clip1 = audioFactory.generateSine(freqC,3.0f);
        // clip1.samples.shrink_to_fit();
        AudioData clip2 = audioFactory.generateSine(freqE,3.0f);
        // clip2.samples.shrink_to_fit();
        AudioData clip3 = audioFactory.generateSine(freqG,3.0f);
        // clip3.samples.shrink_to_fit();
        AudioData clip4 = audioFactory.generateSaw(freqC,3.0f);
        // clip4.samples.shrink_to_fit();


        AudioData clip5 = audioFactory.generateSaw(freqE,3.0f);
        // clip5.samples.shrink_to_fit();

        AudioData clip6 = audioFactory.generateSaw(freqG,3.0f);
        // clip6.samples.shrink_to_fit();

        // debug view setup
        debug1 = debugWaveFormView(clip1,0,0.01f);
        LOG_INFO(1);
        debug2 = debugWaveFormView(clip2,0,0.01f);
        LOG_INFO(2);
        debug3 = debugWaveFormView(clip3,0,0.01f);
        LOG_INFO(3);
        debug4 = debugWaveFormView(clip4,0,0.01f);
        LOG_INFO(4);
        debug5 = debugWaveFormView(clip5,0,0.01f);
        LOG_INFO(5);
        debug6 = debugWaveFormView(clip6,0,0.01f);
        LOG_INFO(6);
        d1ID = m_context.renderer2D->loadImage(debug1);
        d2ID = m_context.renderer2D->loadImage(debug2);
        d3ID = m_context.renderer2D->loadImage(debug3);
        d4ID = m_context.renderer2D->loadImage(debug4);
        d5ID = m_context.renderer2D->loadImage(debug5);
        d6ID = m_context.renderer2D->loadImage(debug6);

        AudioData finalClip = mix({clip1,clip2,clip3});

        clipDebug = debugWaveFormView(finalClip, 0,0.01f);
        clipDebugID = m_context.renderer2D->loadImage(clipDebug);

        finalClip.setVolume(0.4f);

        return finalClip;

    }
};