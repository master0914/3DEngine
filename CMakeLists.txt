cmake_minimum_required(VERSION 3.30)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(3DEngine src/main.cpp
        engine/window/Window.cpp
        engine/core/Sources/Renderer_2D.cpp
        engine/core/Sources/mesh.cpp
        engine/core/Sources/Renderer_3D.cpp
        engine/core/Sources/Camera.cpp
        engine/Math/Vectors/vec2.cpp
        engine/Math/Vectors/vec3.cpp
        engine/Math/Vectors/vec4.cpp
        engine/Math/Vectors/mat4.cpp
        engine/core/Header/Colors.h
)

#add_executable(3DEngine src/main.cpp
#        engine/window/Window.h
#        engine/window/Window.cpp
#        engine/core/Header/Interfaces.h
#        engine/core/Header/Renderer_2D.h
#        engine/core/Header/VectorUtil.h
#        engine/core/Sources/VectorUtil.cpp
#        engine/core/Sources/Colors.cpp
#        engine/core/Sources/Renderer_2D.cpp
#        engine/core/Header/mesh.h
#        engine/core/Sources/mesh.cpp
#        engine/core/Header/Renderer_3D.h
#        engine/core/Header/Camera.h
#        engine/core/Sources/Renderer_3D.cpp
#)

