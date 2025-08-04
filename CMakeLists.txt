cmake_minimum_required(VERSION 3.30)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(3DEngine src/main.cpp
        engine/core/Core.h
        engine/window/Window.h
        engine/window/Window.cpp
        engine/core/Header/Interfaces.h
        engine/core/Header/Renderer_2D.h
        engine/core/Header/VectorUtil.h
        engine/core/Sources/VectorUtil.cpp
        engine/core/Sources/Colors.cpp
        engine/core/Sources/Renderer_2D.cpp)
