//
// Created by augus on 09.03.2026.
//

#ifndef INC_3DENGINE_ICOMPONENT_H
#define INC_3DENGINE_ICOMPONENT_H
#pragma once
#include "EngineContext.h"
#include "GameContainer.h"
#include "../util/Logger.h"

#endif //INC_3DENGINE_ICOMPONENT_H
namespace Engine {
    class IComponent {
    public:
        explicit IComponent(EngineContext& context, GameContainer& container) : m_context(context), m_container(container) {}
        virtual ~IComponent() = default;

        virtual void update(float dt) {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}
        virtual void render() {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}
        virtual void onInit() {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}
        virtual void onExit() {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}

    protected:
        EngineContext& m_context;
        GameContainer& m_container;
    };
}