//
// Created by Master0914 on 11.09.2025.
//
#pragma once
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

// FORWARD DECLARATIONS - keine includes hier!
namespace Engine {
    class IGame;        // Forward declaration
    struct EngineContext; // Forward declaration
}
namespace Engine{

    class GameContainer{
    public:
        GameContainer(int width, int height, const char* title){
            m_context = std::make_shared<EngineContext>();
            m_context->initAllSystems(width,height,title);
        }

        template<typename GameType, typename... Args>
        void createGame(Args&&... args){
            m_game = std::unique_ptr<IGame>(
                    new GameType(*m_context, std::forward<Args>(args)...)
            );
        }

        void run();
    private:
        std::shared_ptr<EngineContext> m_context;
        std::unique_ptr<IGame> m_game;
        int m_targetFPS = 60;
        int m_currentFPS = 0;
        bool m_showFPS = true;
        bool m_running = false;
        bool m_useFrameLimit = true;


        void limitFPS(std::chrono::high_resolution_clock::time_point frameStart);

        void updateStats(std::chrono::high_resolution_clock::time_point currentTime);
    };
}