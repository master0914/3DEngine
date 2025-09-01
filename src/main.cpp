#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include "../engine/window/Window.h"
#include "../engine/core/Header/Renderer_2D.h"
#include "../engine/core/Header/Renderer_3D.h"
#include "../engine/core/Header/VectorUtil.h"
#include "../engine/core/Sources/Colors.cpp"
#include <thread>   // Für std::this_thread
#include <chrono>   // Für std::chrono
#include "../engine/core/Header/mesh.h"

// int main() {
//     Engine::Window window(800, 600, "Software Renderer");
//     Engine::Renderer_2D renderer{};
//
//     while (!window.ShouldClose()) {
//         window.PollEvents();
//
//         window.Clear();
//
//         // Zeichenoperationen
//         Engine::vec2 p1(30,30);
//         Engine::vec2 p2(200,100);
//         Engine::vec2 p3(400,20);
//         renderer.drawTriangle(window, p1, p2,p3,Colors::CYAN);
//
//         window.Present();
//     }
//
//     return 0;
// }

int main(){
    // initialisierung der Renderers
    Engine::Renderer_3D renderer3D{};
    // beginn eines Frames
    renderer3D.beginFrame();

    // laden von objecten und transformieren
    Engine::Mesh mesh{"../objData/test.obj"};
    Engine::mat4 transform{};

    // hinzufügen
    renderer3D.submit(mesh,transform);
    // frame ende: rendern
    renderer3D.endFrame();

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.