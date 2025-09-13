//
// Created by Master0914 on 11.09.2025.
//

#include "TestGame.h"
#include "../../engine/core/header/inputManager.h"

void TestGame::update(float dt){

}
void TestGame::render(){
    m_context.renderer3D->beginFrame();
    // hinzufügen
    m_context.renderer3D->submit(*mesh,*transform);
    // frame ende: Bild wird erstellt
    m_context.renderer3D->endFrame();
    // renderer gibt bild an window
    m_context.renderer3D->present();

}
void TestGame::onInit(){
    std::cout << "init \n";

    mesh = std::make_unique<Engine::Mesh>("../objData/test.obj");
    transform = std::make_unique<Engine::mat4>();

    m_context.camera->setPosition({0, 0, 5});
    m_context.camera->lookAt({0, 0, 0});

    // Debug: Überprüfe ob InputManager existiert
    if (!m_context.input) {
        std::cout << "ERROR: InputManager is null!" << std::endl;
        return;
    }
    if (!m_context.window) {
        std::cout << "ERROR: Window is null!" << std::endl;
        return;
    }



//    m_context.input->setKeyCallback([this](Engine::KeyCode key, Engine::InputState state) {
////        std::cout << "Callback called! Key: " << static_cast<int>(key) << std::endl;
//        this->handleInput(key, state);
//    });


}
void TestGame::onExit(){
    mesh.reset();
    std::cout << "exit\n";
}
//void TestGame::handleInput(Engine::KeyCode key, Engine::InputState state) {
////
//}