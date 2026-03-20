#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include "../engine/core/General/window.h"
#include "../engine/core/General/renderer_2D.h"
#include "../engine/core/3D/renderer_3D.h"

#include <thread>   // Für std::this_thread
#include <chrono>   // Für std::chrono

#include "../engine/core/util/Logger.h"
#include "../engine/core/3D/mesh.h"
#include "Tester/Tester.h"
#include "../engine/core/general/inputManager.h"
#include "../engine/math/Vectors/vector.h"
#include "Tester/TestComponentsGame.h"

// 3D testing

int main(){
    Engine::GameContainer gc{800,800,"pupsi"};
    gc.setShowFPS(false);
    gc.createGame<TestComponentsGame>();
    gc.run();
    return 0;
}



