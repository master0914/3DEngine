add_library(Engine
        core/sources/window.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Plattformspezifische Bibliotheken
if(WIN32)
    target_link_libraries(Engine PRIVATE user32 gdi32)
endif()