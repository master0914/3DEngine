//
// Created by Master0914 on 03.08.2025.
//

#include <cstdint>

#include "../../Math/Vectors/VectorUtil.h"

#ifndef INC_3DENGINE_INTERFACES_H
#define INC_3DENGINE_INTERFACES_H

#endif //INC_3DENGINE_INTERFACES_H
#pragma once

namespace Engine {
    // Basis-Event-System
    struct IEventDispatcher {
        virtual void PollEvents() = 0;
        virtual bool ShouldClose() const = 0;
    };

    // Rendering-Schnittstelle
    struct IRenderer {
        virtual void Clear() = 0;
        virtual void Present() = 0;
        virtual void DrawPixel(int x, int y, uint32_t color) = 0;
        virtual void DrawPixel(vec2& vec, uint32_t color) = 0;
    };

    // Update-Logik
    struct IUpdatable {
        virtual void Update(float deltaTime) = 0;
    };
}
