//
// Created by Master0914 on 11.09.2025.
//

#include "TestGame.h"
#include "../../engine/core/header/inputManager.h"

void TestGame::update(float dt){
    handleInput(dt);
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

    m_container.setTargetFPS(60);

    mesh = std::make_unique<Engine::Mesh>("../objData/suzanne.obj");
    transform = std::make_unique<Engine::mat4>();

    m_context.camera->setPosition({-4, 1, 10});
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
//        std::cout << "Callback called! Key: " << static_cast<int>(key) << std::endl;
//        this->handleInput(key, state);
//    });


}
void TestGame::onExit(){
    mesh.reset();
    std::cout << "exit\n";
}
void TestGame::handleInput(float dt) {
    Engine::vec3 movement;
    if (m_context.input->isKeyPressed(Engine::KeyCode::KEY_W)) {
        movement.z += 1.0f; // Vorwärts
    }
    if (m_context.input->isKeyPressed(Engine::KeyCode::KEY_S)) {
        movement.z -= 1.0f; // Rückwärts
    }
    if (m_context.input->isKeyPressed(Engine::KeyCode::KEY_A)) {
        movement.x -= 1.0f; // Links
    }
    if (m_context.input->isKeyPressed(Engine::KeyCode::KEY_D)) {
        movement.x += 1.0f; // Rechts
    }
    if (m_context.input->isKeyPressed(Engine::KeyCode::KEY_Q)) {
        movement.y -= 1.0f; // Runter
    }
    if (m_context.input->isKeyPressed(Engine::KeyCode::KEY_E)) {
        movement.y += 1.0f; // Hoch
    }
    // movement vektorhier schon erstellt
    // hier normalisieren sodass schräge bewegungen nicht schneller sind
    if(movement.length() > 0.0f){
        movement = movement.normalized() * m_movespeed * dt;
    }

    if(movement.length() > 0.0f){
        m_context.camera->move(movement);
    }
}