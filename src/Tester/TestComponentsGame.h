//
// Created by augus on 09.03.2026.
//

#ifndef INC_3DENGINE_TESTCOMPONENTSGAME_H
#define INC_3DENGINE_TESTCOMPONENTSGAME_H
#include "../../engine/Assets/Button.h"
#include "../../engine/Assets/DragField.h"
#include "../../engine/Assets/Slider.h"
#include "../../engine/Assets/textField.h"

#endif //INC_3DENGINE_TESTCOMPONENTSGAME_H

#pragma once
#include "../../engine/interface/IGame.h"
#include "../../engine/core/3D/mesh.h"
#include "../../engine/interface/GameContainer.h"

class TestComponentsGame: public Engine::IGame{
public:
    explicit TestComponentsGame(Engine::EngineContext& context, Engine::GameContainer& container) : IGame(context,container) {
        button.setOnClick([](){
        });
        // slider.setRange(20,50,30);
        field.registerCallback();

    }
    void update(float dt) override{
        button.update(dt);
        //slider.update(dt);
        field.update(dt);
        drag.update(dt);
    }
    void render() override{
        button.render();
        // slider.render();
        field.render();
        drag.render();
        m_context.renderer2D->present();
    }
    void onInit() override{}
    void onExit() override{}
    void handleInput(float dt);
private:
    // Button button = Button{m_context,m_container,ivec2{100,100},ivec2{1,1},Colors::GREEN, Colors::BLACK,true,"HI"};
    Button button = Button{m_context,m_container,{
        .pos = {100,100},
        .padding = {10,10},
        .buttonColor = 0xff333333,
        .textColor = 0xffffffff,
        .filled = true,
        .text = "hello"
    }};
    // Slider<float> slider = Slider<float>{m_context,m_container,ivec2{100,200},ivec2{100,40}, 5};

    Slider<float> slider = Slider<float>(m_context,m_container,SliderConfigWithStepSize<float>{
        .pos = {100, 200},
        .size = {500, 40},
        .sliderWidth = 20,
        .backgroundColor = 0xffff0000,
        .sliderColor = 0xff0000ff,
        .from = 0.0f,
        .to = 10.0f,
        .stepSize = 1
    });
    TextField field = TextField{m_context,m_container, TextFieldConfig{
        .pos = {200,100},
        .size = {100,40},
        .fillTextField = true,
        .backgroundColor = 0xff555555,
        .textColor = 0xff00ff00,
        .renderInputPrompt = true,
        .inputPrompt = "> ",
        .maxCharacters = 10
    }};
    DragField<float> drag = DragField<float>{m_context,m_container,DragFieldConfig<float>{
        .pos = {200,200},
        .size = {40,20},
        .backgroundColor = 0xff222222,
        .textColor = 0xffffffff,
        .from = 150,
        .to = 1000,
        .stepSize = 1
    }};
};