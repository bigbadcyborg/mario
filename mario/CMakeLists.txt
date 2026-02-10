cmake_minimum_required(VERSION 3.9)

project(mario LANGUAGES CXX)

add_library(mario_core
    src/SDL_Plotter.cpp
    src/functions.cpp
)

target_compile_features(mario_core PUBLIC cxx_std_11)

target_include_directories(mario_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(mario
    src/main.cpp
)

target_link_libraries(mario
    PRIVATE
        mario_core
        SDL2main
        SDL2
        SDL2_mixer
)

if(MINGW)
    target_link_libraries(mario PRIVATE mingw32)
    target_link_options(mario PRIVATE -static-libgcc -static-libstdc++)
endif()

add_custom_command(
    TARGET mario POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:mario>/assets
    COMMENT "Copying game assets to output directory"
)
