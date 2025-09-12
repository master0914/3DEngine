//
// Created by Master0914 on 11.09.2025.
//

#ifndef INC_3DENGINE_IGAME_H
#define INC_3DENGINE_IGAME_H

#endif //INC_3DENGINE_IGAME_H

#pragma once
#include "EngineContext.h"

namespace Engine{
    class IGame{
        public:
        explicit IGame(EngineContext& context) : m_context(context) {}
            virtual ~IGame() = default;
            virtual void update(float dt) = 0;
            virtual void render() = 0;
            virtual void onInit() = 0;
            virtual void onExit() = 0;

    protected:
            EngineContext& m_context;
    };
}

