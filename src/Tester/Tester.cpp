//
// Created by Master0914 on 07.09.2025.
//

#include "../../engine/core/General/window.h"
#include "../../engine/core/General/renderer_2D.h"
#include "../../engine/core/3D/renderer_3D.h"
#include "../../engine/core/util/colors.h"
#include "../../engine/math/Vectors/VectorUtil.h"

#include <thread>   // Für std::this_thread
#include <chrono>   // Für std::chrono
#include "../../engine/core/3D/mesh.h"
// #include "../../engine/core/LEGACY/debug.h"
#include "Tester.h"
#include "../../engine/interface/GameContainer.h"
#include "Test3DGame.h"
#include "../../engine/core/General/image.h"
#include "../../engine/core/util/Logger.h"


void test3D(){
    // initialisierung des Windows
    Engine::Window window{400,400, "hello world"};
    // initialisierung des Renderers
    Engine::Renderer_3D renderer3D{window};
    // initialisierung der Camera
    Engine::Camera camera{};
    // camera auf 0 0 0 gucken lassen
    camera.setPosition(vec3{0.0f,0.0f,7.0f});
    camera.lookAt(vec3{-4.0f,0.0f,0.0f});
    // zuweisen der camera
    renderer3D.setCamera(camera);
    // laden von objecten und transformieren
    Engine::Mesh mesh{"../objData/suzanne.obj"};
    mat4 transform = mat4::Translation(0,0,0);

//    Engine::mat4 view = camera.getViewMatrix();
//    std::cout << "view: \n" << view;
//    Engine::mat4 projection = camera.getProjectionMatrix();
//    std::cout << "projection: \n" << projection;
//    Engine::mat4 pmv = view * projection;
//    std::cout << "projevtion multi view: \n" << pmv;


    while (!window.ShouldClose()) {
        // sorgt für eventHandeling eg Schließen des Fensters, wenn man auf das X drückt
        window.PollEvents();
        LOG_INFO("Pollevents complete \n");
        // beginn eines Frames
        renderer3D.beginFrame();
        LOG_INFO("BeginFrame complete \n");
        // hinzufügen
        renderer3D.submit(mesh,transform);
        LOG_INFO("Submit complete \n");
        // frame ende: Bild wird erstellt
        renderer3D.endFrame();
        LOG_INFO("Endframe complete \n");
        // renderer gibt bild an window
        renderer3D.present();
    }
    }
void test2D(){
    Engine::Window window(800, 800, "Software Renderer");
    Engine::Renderer_2D renderer{window};
    // Engine::Image image{};
    int imgID = renderer.loadImage("C:/Users/augus/CLionProjects/3DEngine/src/Tester/img.png");

     while (!window.ShouldClose()) {
         window.PollEvents();
         renderer.beginFrame();
         // renderer.drawImage(imgID,10,10);
         renderer.drawTileFromImage(imgID,200,200,1,1,64);
         renderer.present();
     }
    }
void testDebug(){
    LOG_INFO("hollo world");
}
void testMesh(){
    Engine::Mesh mesh{"../objData/test.obj"};

}
void testEngine(){
    Engine::GameContainer gc{800,800,"pupsi"};
    gc.createGame<Test3DGame>();
    gc.run();
}

//drawing wireframe from triangle 5
//Line from (160.275,239.725) to (239.725,239.725)
//Line from (239.725,239.725) to (239.725,160.275)
//Line from (239.725,160.275) to (160.275,239.725)
