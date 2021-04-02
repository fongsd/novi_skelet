cmake_minimum_required(VERSION 3.17)
project(skelet)

set(CMAKE_CXX_STANDARD 14)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(glad/)
add_executable(skelet main.cpp)

target_link_libraries(skelet glad glfw OpenGL::GL pthread
        X11 Xrandr Xi dl)