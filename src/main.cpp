#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include "../engine/core/Header/window.h"
#include "../engine/core/Header/renderer_2D.h"
#include "../engine/core/Header/renderer_3D.h"
#include "../engine/Math/Vectors/VectorUtil.h"

#include <thread>   // Für std::this_thread
#include <chrono>   // Für std::chrono
#include "../engine/core/Header/mesh.h"
#include "Tester/Tester.h"
#include "../engine/core/header/inputManager.h"

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


// 3D testing

int main(){
    testEngine();
    return 0;
}



