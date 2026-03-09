//
// Created by augus on 09.03.2026.
//

#ifndef INC_3DENGINE_TESTCOMPONENTSGAME_H
#define INC_3DENGINE_TESTCOMPONENTSGAME_H
#include "../../engine/Assets/Button.h"

#endif //INC_3DENGINE_TESTCOMPONENTSGAME_H

#pragma once
#include "../../engine/interface/IGame.h"
#include "../../engine/core/3D/mesh.h"
#include "../../engine/interface/GameContainer.h"

class TestComponentsGame: public Engine::IGame{
public:
    explicit TestComponentsGame(Engine::EngineContext& context, Engine::GameContainer& container) : IGame(context,container) {
        button.setOnClick([](){
            std::cout << "clicked\n";
        });
    }
    void update(float dt) override{
        button.update(dt);
    }
    void render() override{
        button.render();
        m_context.renderer2D->present();
    }
    void onInit() override{}
    void onExit() override{}
    void handleInput(float dt);
private:
    Button button = Button{m_context,m_container,vec2{100,100},vec2{1,1},Colors::GREEN, Colors::BLACK,true,"Asdfgjhaogihaljkfhkjaswrf"};
};