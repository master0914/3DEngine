if(WIN32)
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/engine/SDL2/SDL2.dll"
            $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
    )
endif()

# IMPORTANT!!!
# this code copies the SDL.dll to the build-dir if the 3DEngineLib is used in another Programm
# to use this do following:

#       add_executable(MyGame main.cpp)                         # or whatever you include/name it
#       target_link_libraries(MyGame PRIVATE 3DEngineLib)       # linking

# THE IMPORTANT STEP:
#       set(EXECUTABLE_NAME MyGame)
#       include("path/to/3DEngineLib/cmake/CopySDL.cmake")