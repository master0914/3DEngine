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
// WICHTIG @TODO
// struct config   für alle children machen damit konstruktoren nicht gewaltig werden

namespace Engine {
    class IComponent {
    public:
        explicit IComponent(EngineContext& context, GameContainer& container, ivec2 pos, ivec2 size) : m_context(context), m_container(container), m_pos(pos), m_size(size) {}
        explicit IComponent(EngineContext& context, GameContainer& container) : m_context(context), m_container(container) {}
        virtual ~IComponent() = default;

        virtual void update(float dt) {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}
        virtual void render() {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}
        virtual void onInit() {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}
        virtual void onExit() {LOG_WARN("THIS FUNKTION IS NOT IMPLEMENTED");}

        [[nodiscard]] ivec2 getPos() const {return m_pos;}
        [[nodiscard]] ivec2 getSize() const {return m_size;}

    protected:
        ivec2 m_pos;
        ivec2 m_size;

        EngineContext& m_context;
        GameContainer& m_container;
    };
}