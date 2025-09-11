cmake_minimum_required(VERSION 3.30)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(3DEngine src/main.cpp
        engine/core/sources/window.cpp
        engine/core/sources/renderer_2D.cpp
        engine/core/sources/mesh.cpp
        engine/core/sources/renderer_3D.cpp
        engine/core/sources/camera.cpp
        engine/math/Vectors/vec2.cpp
        engine/math/Vectors/vec3.cpp
        engine/math/Vectors/vec4.cpp
        engine/math/Vectors/mat4.cpp
        engine/core/header/colors.h
        engine/core/header/debug.h
        src/Tester/Tester.cpp
        src/Tester/Tester.h
        engine/interface/IGame.h
        engine/interface/GameContainer.h
        engine/interface/EngineContext.h
        engine/interface/GameContainer.cpp
)

target_compile_definitions(3DEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG_MODE>
)

#add_executable(3DEngine src/main.cpp
#        engine/window/Window.h
#        engine/window/Window.cpp
#        engine/core/header/Interfaces.h
#        engine/core/header/Renderer_2D.h
#        engine/core/header/VectorUtil.h
#        engine/core/sources/VectorUtil.cpp
#        engine/core/sources/Colors.cpp
#        engine/core/sources/Renderer_2D.cpp
#        engine/core/header/mesh.h
#        engine/core/sources/mesh.cpp
#        engine/core/header/Renderer_3D.h
#        engine/core/header/Camera.h
#        engine/core/sources/Renderer_3D.cpp
#)

