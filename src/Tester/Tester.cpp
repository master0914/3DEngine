//
// Created by Master0914 on 07.09.2025.
//

#include "../../engine/window/Window.h"
#include "../../engine/core/Header/Renderer_2D.h"
#include "../../engine/core/Header/Renderer_3D.h"
#include "../../engine/core/Header/Colors.h"
#include "../../engine/Math/Vectors/VectorUtil.h"

#include <thread>   // Für std::this_thread
#include <chrono>   // Für std::chrono
#include "../../engine/core/Header/mesh.h"
#include "../../engine/core/Header/Debug.h"
#include "Tester.h"


void test3D(){
    // initialisierung des Windows
    Engine::Window window{400,400, "hello world"};
    // initialisierung des Renderers
    Engine::Renderer_3D renderer3D{window};
    // initialisierung der Camera
    Engine::Camera camera{};
    // camera auf 0 0 0 gucken lassen
    camera.setPosition(Engine::vec3{0.0f,0.0f,7j.0f});
    camera.lookAt(Engine::vec3{-4.0f,0.0f,0.0f});
    // zuweisen der camera
    renderer3D.setCamera(camera);
    // laden von objecten und transformieren
    Engine::Mesh mesh{"../objData/suzanne.obj"};
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
        DEBUG_PRINT("Pollevents complete \n");
        // beginn eines Frames
        renderer3D.beginFrame();
        DEBUG_PRINT("BeginFrame complete \n");
        // hinzufügen
        renderer3D.submit(mesh,transform);
        DEBUG_PRINT("Submit complete \n");
        // frame ende: Bild wird erstellt
        renderer3D.endFrame();
        DEBUG_PRINT("Endframe complete \n");
        // renderer gibt bild an window
        renderer3D.present();
    }
    }
void test2D(){
        Engine::Window window(400, 400, "Software Renderer");
     Engine::Renderer_2D renderer{};

     while (!window.ShouldClose()) {
         window.PollEvents();

         window.Clear();
         uint32_t color = Colors::MAGENTA;
         Engine::vec2 v0{160.275,239.725};
         Engine::vec2 v1{239.725,239.725};
         Engine::vec2 v2{239.725,160.275};



         // Zeichenoperationen
//         renderer.drawLine(window,v1,v2,color);
         renderer.drawTriangle(window,v0,v1,v2,color);

         window.Present();
     }
    }
void testDebug(){
    DEBUG_PRINT("hollo world");
}
void testMesh(){
    Engine::Mesh mesh{"../objData/test.obj"};

}

//drawing wireframe from triangle 5
//Line from (160.275,239.725) to (239.725,239.725)
//Line from (239.725,239.725) to (239.725,160.275)
//Line from (239.725,160.275) to (160.275,239.725)
