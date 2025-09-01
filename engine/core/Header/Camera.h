//
// Created by Master0914 on 01.09.2025.
//

#ifndef INC_3DENGINE_CAMERA_H
#define INC_3DENGINE_CAMERA_H

#endif //INC_3DENGINE_CAMERA_H
#pragma once
#include "../../Math/Vectors/VectorUtil.h"

namespace Engine{
    class Camera{
    public:
        Camera();

        void setPosition(const vec3& position);
        void lookAt(const vec3& target); // Berechnet direction aus target - position
        void setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearPlane, float farPlane);


        const mat4& getProjectionMatrix() const;
        const mat4& getViewMatrix() const;


        const vec3& getPosition() const { return m_Pos; }
        const vec3& getForwardDirection() const { return m_Dir; }
        const vec3& getUpDirection() const { return m_Up; }
        const vec3& getRightDirection() const { return m_Right; }


    private:
        void updateViewMatrix();
        // Berechnet die Projektions-Matrix neu (wird intern aufgerufen, wenn sich FOV/etc. ändert)
        void updateProjectionMatrix();

        // Kamera Parameter (View)
        vec3 m_Pos;
        vec3 m_Dir;   // blickrichtung der camera
        vec3 m_Up;    // welche rchtung oben ist
        vec3 m_Right; // r = dir x up


        // Kamera Parameter (Projection)
        float m_Fov;  // in grad
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        // Matrizen
        mat4 m_ViewMatrix;
        mat4 m_ProjectionMatrix;
        bool m_ViewOld;
        bool m_ProjectionOld;
    };
}