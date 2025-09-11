//
// Created by Master0914 on 11.09.2025.
//
#pragma once
#include <memory>
#include "../core/header/window.h"
#include "../core/header/renderer_3D.h"

#ifndef INC_3DENGINE_ENGINECONTEXT_H
#define INC_3DENGINE_ENGINECONTEXT_H

#endif //INC_3DENGINE_ENGINECONTEXT_H

namespace Engine{
    struct EngineContext {
        void initAllSystems(int width, int height, const char* title){
            window = std::make_shared<Window>(width, height,title);
            renderer2D = std::make_shared<Renderer_2D>();
            renderer3D = std::make_shared<Renderer_3D>(*window);
            camera = std::make_shared<Camera>();

        }

        std::shared_ptr<Window> window;

        std::shared_ptr<Renderer_2D> renderer2D;
        std::shared_ptr<Renderer_3D> renderer3D;

        std::shared_ptr<Camera> camera;
//        std::shared_ptr<InputManager> input;
//        std::shared_ptr<ResourceManager> resources;
//        std::shared_ptr<Scene> scene;
    };



}