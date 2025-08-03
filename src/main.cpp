#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include "../engine/window/Window.h"
#include <thread>   // Für std::this_thread
#include <chrono>   // Für std::chrono

int main() {
    Engine::Window window(800, 600, "Software Renderer");

    while (!window.ShouldClose()) {
        window.PollEvents();

        window.Clear();

        // Zeichenoperationen
        for (int y = 100; y < 200; y++) {
            for (int x = 100; x < 200; x++) {
                window.DrawPixel(x, y, 0xFFFF0000); // Roter Quadrat
            }
        }

        window.Present();
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.