//
// Created by Master0914 on 11.09.2025.
//

#ifndef INC_3DENGINE_TESTGAME_H
#define INC_3DENGINE_TESTGAME_H

#pragma once
#include "../../engine/interface/IGame.h"
#include "../../engine/core/3D/mesh.h"
#include "../../engine/interface/GameContainer.h"

class Test3DGame: public Engine::IGame{
public:
    explicit Test3DGame(Engine::EngineContext& context, Engine::GameContainer& container) : Engine::IGame(context,container){}
    void update(float dt) override;
    void render() override;
    void onInit() override;
    void onExit() override;
    void handleInput(float dt);
private:
    std::unique_ptr<Engine::Mesh> mesh;
    std::unique_ptr<mat4> transform;
    float m_movespeed = 2;
};


#endif //INC_3DENGINE_TESTGAME_H
