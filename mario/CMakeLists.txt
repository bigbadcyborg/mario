cmake_minimum_required(VERSION 3.9)

project(mario)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

add_library(mario_net_protocol
    net/protocol/protocol.cpp
    net/protocol/protocol.h
)

add_executable(mario main.cpp SDL_Plotter.h functions.cpp SDL_Plotter.cpp functions.h)
target_link_libraries(mario SDL2main SDL2 SDL2_mixer)

add_executable(game_server
    game_server.cpp
)
target_link_libraries(game_server mario_net_protocol)

add_executable(game_client
    game_client.cpp
)
target_link_libraries(game_client mario_net_protocol)
add_executable(mario main.cpp SDL_Plotter.h functions.cpp SDL_Plotter.cpp functions.h LevelLoader.cpp LevelLoader.h)
add_executable(mario
    main.cpp
    SDL_Plotter.h
    SDL_Plotter.cpp
    functions.h
    functions.cpp
    src/GameTypes.h
    src/InputSystem.h
    src/InputSystem.cpp
    src/PhysicsSystem.h
    src/PhysicsSystem.cpp
    src/CollisionSystem.h
    src/CollisionSystem.cpp
    src/RenderSystem.h
    src/RenderSystem.cpp
    src/GameRulesSystem.h
    src/GameRulesSystem.cpp
)

target_link_libraries(mario SDL2main SDL2 SDL2_mixer)
