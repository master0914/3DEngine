//
// Created by augus on 03.06.2026.
//

#ifndef INC_3DENGINE_MIXINGPLAYER_H
#define INC_3DENGINE_MIXINGPLAYER_H
#pragma once

#include "IGame.h"
#include "MixingStation.h"
#include "../../engine/core/Audio/audioFactory.h"

#endif //INC_3DENGINE_MIXINGPLAYER_H

class MixingPlayer: public Engine::IGame {
public:
    MixingPlayer(Engine::EngineContext &context, Engine::GameContainer &container)
        : IGame(context, container), mixGUI(context,container){
        mixData = audioFactory.generateSine(1000,1);
        mixedDebugFront = debugWaveFormView(mixData,0,debugViewLength,400,100);
        mixedDebugBack = debugWaveFormView(mixData,mixData.duration() - debugViewLength,debugViewLength,400,100,0xffff0000);
        frontID = m_context.renderer2D->loadImage(mixedDebugFront);
        backID = m_context.renderer2D->loadImage(mixedDebugBack);
    }

    void update(float dt) override {
        mixGUI.update(dt);
        if (mixGUI.isStationDirty()) {
            // LOG_INFO("yeah you filthy!!!!");
            recalculateMix();
            mixGUI.cleanStation();
        }
        if (mixGUI.isPlayingActive()) {
            if (!clipPlaying) {
                LOG_INFO("clip started playing");
                clipPlaying = true;
                clipID = m_context.audio->play(mixData,true,mixGUI.getMasterVolume());
            }
        }
        if (!mixGUI.isPlayingActive()) {
            if (clipPlaying) {
                LOG_INFO("clip stopped playing");
                clipPlaying = false;
                m_context.audio->stop(clipID);
            }
        }
    }


    void recalculateMix() {
        // TODO switch to better mixing algorithm(not init all then mix)
        std::vector settings = mixGUI.getOscillatorSettings();
        std::vector<AudioData> clips;
        for (const auto& s: settings) {
            clips.push_back(generateClipFromSetting(s));
        }
        mixData = mix(clips);

        // draw new images
        mixedDebugFront = debugWaveFormView(mixData,0,debugViewLength,400,100);
        mixedDebugBack = debugWaveFormView(mixData,mixData.duration() - debugViewLength,debugViewLength,400,100,0xffff0000);
        m_context.renderer2D->updateImage(frontID,mixedDebugFront);
        m_context.renderer2D->updateImage(backID,mixedDebugBack);
    }

    AudioData generateClipFromSetting(OscillatorSettings setting) {
        return (setting.isSine == true)?
        (audioFactory.generateSine(setting.frequency,cliplength)):
        (audioFactory.generateSaw(setting.frequency,cliplength));
    }




    void render() override {
        m_context.renderer2D->fillRectangle(0, 0,m_context.window->getm_Height(),m_context.window->getm_Width(),0xff1a1a1a);


        mixGUI.render();

        m_context.renderer2D->drawText("front",600,0,0xff00ff00);
        m_context.renderer2D->drawImage(frontID,600,20);
        m_context.renderer2D->drawText("back", 200,0,0xffff0000);
        m_context.renderer2D->drawImage(backID,200,20);

        m_context.renderer2D->present();
    }

    void onInit() override {
        mixGUI.onInit();
    }

    void onExit() override {
        mixGUI.onExit();
    }

private:
    AudioFactory audioFactory;
    MixingStationGame mixGUI;

    AudioData mixData;
    bool clipPlaying = false;
    int clipID = -1;

    float cliplength = 1.0f;


    int frontID, backID;
    Engine::Image mixedDebugFront;
    Engine::Image mixedDebugBack;
    float debugViewLength = 0.01f;
};