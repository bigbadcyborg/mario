cmake_minimum_required(VERSION 3.9)

project(mario)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_GAME "Build SDL game executable" ON)

add_library(game_logic STATIC game_logic.cpp game_logic.h)

enable_testing()
add_executable(game_logic_tests tests/test_game_logic.cpp)
target_link_libraries(game_logic_tests PRIVATE game_logic)
add_test(NAME game_logic_tests COMMAND game_logic_tests)

if(BUILD_GAME)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

    add_executable(
        mario
        main.cpp
        SDL_Plotter.h
        functions.cpp
        SDL_Plotter.cpp
        functions.h
        game_logic.h
        game_logic.cpp)

    target_link_libraries(mario PRIVATE game_logic SDL2main SDL2 SDL2_mixer)
endif()
