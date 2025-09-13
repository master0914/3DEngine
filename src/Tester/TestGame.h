//
// Created by Master0914 on 11.09.2025.
//

#ifndef INC_3DENGINE_TESTGAME_H
#define INC_3DENGINE_TESTGAME_H

#pragma once
#include "../../engine/interface/IGame.h"
#include "../../engine/core/header/mesh.h"

class TestGame: public Engine::IGame{
public:
    explicit TestGame(Engine::EngineContext& context) : Engine::IGame(context) {}
    void update(float dt) override;
    void render() override;
    void onInit() override;
    void onExit() override;
    void handleInput(Engine::KeyCode key, Engine::InputState state);
private:
    std::unique_ptr<Engine::Mesh> mesh;
    std::unique_ptr<Engine::mat4> transform;
};


#endif //INC_3DENGINE_TESTGAME_H
