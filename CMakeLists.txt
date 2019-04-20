# cmake_minimum_required(VERSION <specify CMake version here>)
project(sdltest)

set(CMAKE_CXX_STANDARD 14)

add_executable(sdltest main.cpp CWindow.cpp CWindow.h CTexture.cpp CTexture.h CTetrisGame.cpp CTetrisGame.h CTetrisPawn.cpp CTetrisPawn.h Vector2D.h Matrix2D.h)
target_link_libraries(sdltest SDL2)
