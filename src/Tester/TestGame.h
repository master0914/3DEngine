//
// Created by Master0914 on 11.09.2025.
//

#ifndef INC_3DENGINE_TESTGAME_H
#define INC_3DENGINE_TESTGAME_H

#pragma once
#include "../../engine/interface/IGame.h"

class TestGame: public Engine::IGame{
public:
    explicit TestGame(Engine::EngineContext& context) : Engine::IGame(context) {}
    void update(float dt);
    void render();
    void onInit();
    void onExit();
};


#endif //INC_3DENGINE_TESTGAME_H
