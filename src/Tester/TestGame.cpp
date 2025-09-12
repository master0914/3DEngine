//
// Created by Master0914 on 11.09.2025.
//

#include "TestGame.h"
#include "../../engine/core/header/inputManager.h"

void TestGame::update(float dt){

    //std::cout << "update \n";
}
void TestGame::render(){
    //std::cout << "render \n";
}
void TestGame::onInit(){
    std::cout << "init \n";

    // Debug: Überprüfe ob InputManager existiert
    if (!m_context.input) {
        std::cout << "ERROR: InputManager is null!" << std::endl;
        return;
    }
    if (!m_context.window) {
        std::cout << "ERROR: Window is null!" << std::endl;
        return;
    }

    m_context.input->setKeyCallback([this](Engine::KeyCode key, Engine::InputState state) {
        std::cout << "Callback called! Key: " << static_cast<int>(key) << std::endl;
        this->handleInput(key, state);
    });

    std::cout << "Callback registered successfully!" << std::endl;
}
void TestGame::onExit(){
    std::cout << "exit\n";
}
void TestGame::handleInput(Engine::KeyCode key, Engine::InputState state) {
    if (state == Engine::InputState::JUST_PRESSED) {
        //std::cout << "Key " << keyCodeToString(key) << "pressed \n" << std::endl;
    }
}