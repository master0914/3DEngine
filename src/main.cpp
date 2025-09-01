#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include "../engine/window/Window.h"
#include "../engine/core/Header/Renderer_2D.h"
#include "../engine/core/Header/Renderer_3D.h"
#include "../engine/Math/Vectors/VectorUtil.h"

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

//    int main() {
//
//        // Teste die Matrixmultiplikation
//        Engine::mat4 testMatrix{};
//        Engine::vec4 testVertex(1, 2, 3, 1);
//        Engine::vec4 result = testMatrix * testVertex; // Sollte (1, 2, 3, 1) sein
//
//// Teste mit deiner MVP-Matrix
//        Engine::mat4 mvp; // Deine MVP-Matrix wie oben
//        Engine::vec4 vertex(1, -1, 1, 1);
//        Engine::vec4 result = mvp * vertex;
//        std::cout << "Matrix multiplication test: " << result.x << ", " << result.y << ", " << result.z << ", " << result.w << std::endl;
//    }


int main(){
    // initialisierung des Windows
    Engine::Window window{400,400, "hello world"};
    // initialisierung des Renderers
    Engine::Renderer_3D renderer3D{window};
    // initialisierung der Camera
    Engine::Camera camera{};
    // camera auf 0 0 0 gucken lassen
    camera.setPosition(Engine::vec3{0.0f,0.0f,5.0f});
    camera.lookAt(Engine::vec3{0.0f,0.0f,0.0f});
    // zuweisen der camera
    renderer3D.setCamera(camera);
    // laden von objecten und transformieren
    Engine::Mesh mesh{"../objData/test.obj"};
    Engine::mat4 transform = Engine::mat4::Translation(0,0,0);

//    Engine::mat4 view = camera.getViewMatrix();
//    std::cout << "view: \n" << view;
//    Engine::mat4 projection = camera.getProjectionMatrix();
//    std::cout << "projection: \n" << projection;
//    Engine::mat4 pmv = view * projection;
//    std::cout << "projevtion multi view: \n" << pmv;


    while (!window.ShouldClose()) {
        // sorgt für eventHandeling eg Schließen des Fensters, wenn man auf das X drückt
        window.PollEvents();
        std::cout << "Pollevents complete \n";
        // beginn eines Frames
        renderer3D.beginFrame();
        std::cout << "BeginFrame complete \n";
        // hinzufügen
        renderer3D.submit(mesh,transform);
        std::cout << "Submit complete \n";
        // frame ende: Bild wird erstellt
        renderer3D.endFrame();
        std::cout << "Endframe complete \n";
        // renderer gibt bild an window
        renderer3D.present();
        window.Present();
    }

    return 0;
}



// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.