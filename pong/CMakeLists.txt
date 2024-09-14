cmake_minimum_required(VERSION 3.28)

project(Pongduino)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
    pong 
    main.cpp 
    pong.cpp 
    gameArea.cpp 
    score.cpp 
    ../controller/keyboard.cpp 
    ../controller/serialRead.cpp
    ../controller/arduino.cpp
    ../multiplayer/communication.cpp
    ../multiplayer/gameserver.cpp
    ../multiplayer/client.cpp
    ../multiplayer/server.cpp
    ../assets/paddle.cpp
    ../assets/ball.cpp
    ../assets/ballview.cpp
    ../assets/paddleview.cpp
    ../assets/paddlevirtual.cpp
)
find_path(RL_INCLUDE_DIR NAMES raylib.h PATHS /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})
find_library(RL_LIBRARY NAMES raylib PATHS /opt/homebrew/opt/raylib/lib)
target_link_libraries(pong ${RL_LIBRARY})
