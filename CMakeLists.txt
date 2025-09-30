cmake_minimum_required(VERSION 3.30)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)


include_directories(lib/stb)


add_library(3DEngineLib STATIC
        engine/core/sources/window.cpp
        engine/core/sources/renderer_2D.cpp
        engine/core/sources/mesh.cpp
        engine/core/sources/renderer_3D.cpp
        engine/core/sources/camera.cpp
        engine/math/Vectors/vec2.cpp
        engine/math/Vectors/vec3.cpp
        engine/math/Vectors/vec4.cpp
        engine/math/Vectors/mat4.cpp
        engine/core/sources/inputManager.cpp
        engine/core/sources/bufferRenderer2D.cpp
        engine/interface/GameContainer.cpp
        engine/core/sources/image.cpp
)

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
        engine/interface/GameContainer.cpp
        src/Tester/TestGame.cpp
        engine/core/header/inputManager.h
        engine/core/sources/inputManager.cpp
        engine/core/header/bufferRenderer2D.h
        engine/core/sources/bufferRenderer2D.cpp
        engine/core/header/image.h
        engine/core/sources/image.cpp
)

target_link_libraries(3DEngine 3DEngineLib)


target_include_directories(3DEngineLib PUBLIC
        engine/core/header
        engine/math/Vectors
        engine/interface
        lib/stb
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

