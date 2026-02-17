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
        engine/core/header/Logger.h
)

if(WIN32)
    set(SDL2_INCLUDE_DIR "C:/CodingLibs/SDL2/x86_64-w64-mingw32/include")
    set(SDL2_LIB_DIR "C:/CodingLibs/SDL2/x86_64-w64-mingw32/lib")

    target_include_directories(3DEngineLib PUBLIC ${SDL2_INCLUDE_DIR})
    # Linker-Pfad setzen
    link_directories(${SDL2_LIB_DIR})

    # Reihenfolge ist wichtig: mingw32, SDL2main, SDL2, dann Windows-Libs
    target_link_libraries(3DEngineLib PUBLIC
            mingw32
            "${SDL2_LIB_DIR}/libSDL2main.a"
            "${SDL2_LIB_DIR}/libSDL2.a"
            user32
            gdi32
            kernel32
            winspool
            shell32
            ole32
            oleaut32
            uuid
            comdlg32
            advapi32
            setupapi
            imm32
            winmm
            cfgmgr32
            version
    )
elseif(UNIX)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(3DEngineLib PRIVATE ${SDL2_LIBRARIES})
endif()

add_executable(3DEngine src/main.cpp
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
        engine/core/header/bitmapFont.h
        engine/core/sources/bitmapFont.cpp
        engine/core/sources/window.cpp
        engine/core/header/Logger.h
)
target_link_libraries(3DEngine PUBLIC 3DEngineLib)

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

