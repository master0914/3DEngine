cmake_minimum_required(VERSION 3.30)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib/stb)

# SDL PATHS----------------------------------------------------------------------
set(SDL2_DLL_PATH "${PROJECT_SOURCE_DIR}/engine/SDL2/SDL2.dll")
set(SDL2_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/SDL2/include")
set(SDL2_LIB_DIR "${PROJECT_SOURCE_DIR}/engine/SDL2/lib/x64") # adjust if needed

# Engine Library----------------------------------------------------------------------
add_library(3DEngineLib STATIC
        engine/core/General/window.cpp
        engine/core/General/renderer_2D.cpp
        engine/core/3D/mesh.cpp
        engine/core/3D/renderer_3D.cpp
        engine/core/3D/camera.cpp
        engine/math/Vectors/vec2.cpp
        engine/math/Vectors/vec3.cpp
        engine/math/Vectors/vec4.cpp
        engine/math/Vectors/mat4.cpp
        engine/core/General/inputManager.cpp
        engine/core/3D/bufferRenderer2D.cpp
        engine/interface/GameContainer.cpp
        engine/core/General/image.cpp
        engine/core/util/Logger.h
        engine/math/Vectors/vector.h
        engine/math/Vectors/mat4.h
        engine/Assets/IComponent.h
        engine/Assets/Button.h
        engine/Assets/Slider.h
)
target_include_directories(3DEngineLib PUBLIC
        engine/core/header
        engine/math/Vectors
        engine/interface
        lib/stb
        ${SDL2_INCLUDE_DIR}
)

target_link_directories(3DEngineLib PUBLIC ${SDL2_LIB_DIR})

# SDL-linking----------------------------------------------------------------------
if(WIN32)
    target_link_libraries(3DEngineLib PUBLIC
            SDL2.lib
            SDL2main.lib
            # Windows-Standard-Libs
            user32.lib
            gdi32.lib
            kernel32.lib
            winspool.lib
            shell32.lib
            ole32.lib
            oleaut32.lib
            uuid.lib
            comdlg32.lib
            advapi32.lib
            setupapi.lib
            imm32.lib
            winmm.lib
            cfgmgr32.lib
            version.lib
    )

elseif(UNIX)
    find_package(SDL2 REQUIRED)
    target_include_directories(3DEngineLib PUBLIC ${SDL2_INCLUDE_DIRS})
    target_link_libraries(3DEngineLib PRIVATE ${SDL2_LIBRARIES})
endif()


# Executable----------------------------------------------------------------------

add_executable(3DEngine
        src/main.cpp
        src/Tester/Tester.cpp
        src/Tester/Test3DGame.cpp
        src/Tester/TestComponentsGame.h

)
target_link_libraries(3DEngine PRIVATE 3DEngineLib)



# Copy to build file(only for using this project as an executable NOT FOR LIBRARY)
if(WIN32)
    add_custom_target(copy_sdl2 ALL
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DLL_PATH}"
            $<TARGET_FILE_DIR:3DEngine>
    )
    add_dependencies(3DEngine copy_sdl2)
endif ()

# Compile definition----------------------------------------------------------------------
target_compile_definitions(3DEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG_MODE>
)

