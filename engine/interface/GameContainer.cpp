//
// Created by Master0914 on 11.09.2025.
//

#include "GameContainer.h"

namespace Engine{






    void GameContainer::run() {
        if (!m_game) {
            throw std::runtime_error("No game initialized!");
        }

        m_game->onInit();
        m_running = true;


        using Clock = std::chrono::high_resolution_clock;
        using Seconds = std::chrono::duration<double>;

        // time shit
        auto lastTime = Clock::now();
        double accumulator = 0.0;
        double frameTime = 1.0 / m_targetFPS;

        while (m_running && !m_context->window->ShouldClose()) {
            m_context->window->PollEvents();
            // zeit berechnen!    wieso muss diese scheiße so kompliziert sein lass mich doch einfach zeit holen smh
            auto currentTime = Clock::now();
            double deltaTime = std::chrono::duration_cast<Seconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            accumulator += deltaTime;

            // input verarbeiten
//                m_context.input->update();

            while (accumulator >= frameTime) {
                m_context->input->update();
                m_game->update(static_cast<float>(frameTime));
                m_context->input->endFrame();
                accumulator -= frameTime;
            }

            m_game->render();


            // FPS Controlling
            limitFPS(currentTime);

            // Statistik
            updateStats(currentTime);

            // Buffer swap und Events
//                m_context->window->swapBuffers();

        }

        // Aufräumen
        m_game->onExit();
    }

    void GameContainer::limitFPS(std::chrono::high_resolution_clock::time_point frameStart) {
        if (!m_useFrameLimit) return;

        using Seconds = std::chrono::duration<double>;
        auto frameEnd = frameStart + std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::duration<double>(1.0 / m_targetFPS)
        );

        // Präzises Warten
        while (std::chrono::high_resolution_clock::now() < frameEnd) {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }

    void GameContainer::updateStats(std::chrono::high_resolution_clock::time_point currentTime) {
        using Seconds = std::chrono::duration<double>;
        static auto lastStatsTime = currentTime;
        static int frameCount = 0;

        frameCount++;

        if (std::chrono::duration_cast<Seconds>(currentTime - lastStatsTime).count() >= 1.0) {
            m_currentFPS = frameCount;
            frameCount = 0;
            lastStatsTime = currentTime;

            if (m_showFPS) {
                std::cout << "FPS: " << m_currentFPS
                          << " | Target: " << m_targetFPS
                          << " | Delta: " << (m_currentFPS - m_targetFPS) << std::endl;
            }
        }
    }
}