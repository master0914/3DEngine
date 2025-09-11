//
// Created by Master0914 on 11.09.2025.
//
#include "IGame.h"
#include "EngineContext.h"
#include <memory>
#include <chrono>
#include <thread>
#include "../core/header/window.h"
#include "../core/header/renderer_3D.h"


#ifndef INC_3DENGINE_GAMECONTAINER_H
#define INC_3DENGINE_GAMECONTAINER_H

#endif //INC_3DENGINE_GAMECONTAINER_H


namespace Engine{

    class GameContainer{
    public:
        GameContainer(int width, int height, const char* title){
            m_context = std::make_shared<EngineContext>();
            m_context->initAllSystems(width,height,title);
        }

        template<typename GameType, typename... Args>
        void createGame(Args&&... args) {
            m_game = std::make_unique<GameType>(*m_context, std::forward<Args>(args)...);
        }

        void run() {
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
                // zeit berechnen!    wieso muss diese scheiße so kompliziert sein lass mich doch einfach zeit holen smh
                auto currentTime = Clock::now();
                double deltaTime = std::chrono::duration_cast<Seconds>(currentTime - lastTime).count();
                lastTime = currentTime;

                accumulator += deltaTime;

                // input verarbeiten
//                m_context.input->update();

                while (accumulator >= frameTime) {
                    m_game->update(static_cast<float>(frameTime));
                    accumulator -= frameTime;
                }

                m_game->render();

                // FPS Controlling
                limitFPS(currentTime);

                // Statistik
                updateStats(currentTime);

                // Buffer swap und Events
//                m_context->window->swapBuffers();
                m_context->window->PollEvents();
            }

            // Aufräumen
            m_game->onExit();
        }
    private:
        std::shared_ptr<EngineContext> m_context;
        std::shared_ptr<IGame> m_game;
        int m_targetFPS = 60;
        int m_currentFPS = 0;
        bool m_showFPS = true;
        bool m_running = false;
        bool m_useFrameLimit = true;




        void limitFPS(std::chrono::high_resolution_clock::time_point frameStart) {
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

        void updateStats(std::chrono::high_resolution_clock::time_point currentTime) {
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
    };
}