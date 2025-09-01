//
// Created by Master0914 on 01.09.2025.
//

#ifndef INC_3DENGINE_CAMERA_H
#define INC_3DENGINE_CAMERA_H

#endif //INC_3DENGINE_CAMERA_H
#pragma once
#include "VectorUtil.h"

namespace Engine{
    class Camera{
    public:
        mat4 getProjectionMatrix() const;
        mat4 getViewMatrix() const;
    };
}