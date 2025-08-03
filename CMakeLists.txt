cmake_minimum_required(VERSION 3.30)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(3DEngine src/main.cpp
        engine/core/Core.h
        engine/window/Window.h
        engine/window/Window.cpp
        engine/core/Interfaces.h)
