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
#include "../engine/core/Audio/wavLoader.h"
#include "Tester/Tester.h"
#include "../engine/core/general/inputManager.h"
#include "../engine/math/Vectors/vector.h"
#include "Tester/AudioTest.h"
// #include "Tester/TestComponentsGame.h"
#include "../engine/core/Audio/fft.h"
#include "Tester/MixingStation/MixingPlayer.h"
#include "Tester/MixingStation/MixingStation.h"


int main(){
    Engine::GameContainer gc{1600,1000,"hallo"};
    gc.setShowFPS(false);
    gc.createGame<MixingPlayer>();
    gc.run();

    // float freqE = getFrequency(Note::C,5);
    // AudioFactory audioFactory;
    // AudioData clip5 = audioFactory.generateSaw(freqE,3.0f);
    //
    // Engine::Image debug5 = debugWaveFormView(clip5,0,0.01f);

    return 0;
}



