//
// Created by Master0914 on 01.09.2025.
//

#include <cmath>
#include "../Header/Camera.h"

namespace Engine {

    Camera::Camera()
            : m_Pos(0.0f, 0.0f, 0.0f),
              m_Dir(0.0f, 0.0f, -1.0f), // Schaut entlang der negativen Z-Achse
              m_Up(0.0f, 1.0f, 0.0f),
              m_Right(1.0f, 0.0f, 0.0f),
              m_Fov(80.0f),
              m_AspectRatio(1.0f),
              m_NearPlane(0.1f),
              m_FarPlane(100.0f),
              m_ViewOld(true),
              m_ProjectionOld(true) {
    }

    void Camera::setPosition(const vec3 &position) {
        m_Pos = position;
        m_ViewOld = true; // ViewMatrix muss neu berechnet werden
    }

    void Camera::lookAt(const vec3& target) {
        m_Dir = (target - m_Pos).normalized();

        // Temporärer Rechts-Vektor berechnen
        vec3 tempRight = vec3(0.0f, 1.0f, 0.0f).cross(m_Dir).normalized();

        // Wenn Blickrichtung parallel zu Welt-Up, verwende alternativen Up
        if (tempRight.length() < 0.001f) {
            tempRight = vec3(1.0f, 0.0f, 0.0f).cross(m_Dir).normalized();
        }

        m_Right = tempRight;
        m_Up = m_Dir.cross(m_Right).normalized();

        m_ViewOld = true;
    }

    void Camera::setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearPlane, float farPlane) {
        m_Fov = fieldOfViewDegrees;
        m_AspectRatio = aspectRatio;
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;
        m_ProjectionOld = true;
    }

    const mat4& Camera::getViewMatrix() const {
        if (m_ViewOld) {
            // "LookAt" Matrix berechnen:
            // Sie erzeugt eine View-Matrix, die von m_Position in Richtung m_Forward schaut,
            // mit m_Up als Oben-Vektor.
            // Da die Matrix neu berechnet wird, casten wir das Dirty-Flag weg.
            const_cast<Camera *>(this)->updateViewMatrix();
        }
        return m_ViewMatrix;
    }

    const mat4& Camera::getProjectionMatrix() const {
        if (m_ProjectionOld) {
            const_cast<Camera *>(this)->updateProjectionMatrix();
        }
        return m_ProjectionMatrix;
    }

    void Camera::updateViewMatrix() {
        // Implementierung der "LookAt" Matrix.
        // Siehe: https://learnopengl.com/Getting-started/Camera
        // Basis-Idee:
        // R = Rechts-Vektor (already calculated)
        // U = Oben-Vektor (already calculated)
        // F = Blickrichtung (already calculated)
        // P = Position

        // ViewMatrix = [
        //  [R.x, R.y, R.z, -dot(R, P)],
        //  [U.x, U.y, U.z, -dot(U, P)],
        //  [F.x, F.y, F.z, -dot(F, P)],
        //  [0,   0,   0,    1        ]
        // ]
        mat4 V;
        V.m = {
                // Spalte 0 = Right
                m_Right.getX(), m_Right.getY(), m_Right.getZ(), 0.0f,

                // Spalte 1 = Up
                m_Up.getX(), m_Up.getY(), m_Up.getZ(), 0.0f,

                // Spalte 2 = -Dir
                -m_Dir.getX(), -m_Dir.getY(), -m_Dir.getZ(), 0.0f,

                // Spalte 3 = Translation
                -m_Right.dot(m_Pos), -m_Up.dot(m_Pos), m_Dir.dot(m_Pos), 1.0f
        };
        m_ViewMatrix = V;
        m_ViewOld = false;
    }

    void Camera::updateProjectionMatrix() {
        // Implementierung der Perspektiv-Projektions-Matrix.
        // Siehe: https://learnopengl.com/Getting-started/Coordinate-Systems
        auto fovRad = static_cast<float>(m_Fov * (M_PI / 180.0)); // Grad zu Bogenmaß
        float tanHalfFov = std::tan(fovRad / 2.0f);
        float range = m_FarPlane - m_NearPlane;

        m_ProjectionMatrix = mat4::Zero();
        m_ProjectionMatrix(0, 0) = 1.0f / (m_AspectRatio * tanHalfFov);
        m_ProjectionMatrix(1, 1) = 1.0f / tanHalfFov;
        m_ProjectionMatrix(2, 2) = -(m_NearPlane + m_FarPlane) / range;
        m_ProjectionMatrix(2, 3) = -(2.0f * m_FarPlane * m_NearPlane) / range;
        m_ProjectionMatrix(3, 2) = -1.0f;
        // Oder verwende eine fertige perspective-Funktion in deiner mat4 Klasse.

        m_ProjectionOld = false;
    }


}
