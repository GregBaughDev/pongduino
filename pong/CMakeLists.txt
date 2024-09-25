cmake_minimum_required(VERSION 3.28)

project(Pongduino)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(
    pong 
    main.cpp 
    pong.cpp 
    gamearea.cpp 
    score.cpp 
    ../controller/keyboard.cpp 
    ../controller/serialRead.cpp
    ../controller/arduino.cpp
    ../controller/controller.cpp
    ../multiplayer/communication.cpp
    ../multiplayer/client.cpp
    ../assets/ball.cpp
    ../assets/paddle.cpp
    ../assets/ballview.cpp
    ../assets/paddleview.cpp
)

add_executable(
    pong-server
    serverCreate.cpp
    gamearea.cpp 
    score.cpp
    ../multiplayer/gameserver.cpp
    ../multiplayer/server.cpp
    ../multiplayer/communication.cpp
    ../assets/ball.cpp
    ../assets/paddlevirtual.cpp
    ../assets/paddleview.cpp
    ../assets/paddle.cpp
    ../assets/ballview.cpp
)

find_path(RL_INCLUDE_DIR NAMES raylib.h PATHS /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})
find_library(RL_LIBRARY NAMES raylib PATHS /opt/homebrew/opt/raylib/lib)
target_link_libraries(pong ${RL_LIBRARY})
target_link_libraries(pong-server ${RL_LIBRARY})
add_custom_command(TARGET pong POST_BUILD COMMAND cp pong pong-p1 && mv pong pong-p2)
add_custom_command(TARGET pong-server POST_BUILD COMMAND bash -c echo GREG)
