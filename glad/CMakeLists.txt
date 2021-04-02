cmake_minimum_required(VERSION 3.0)
project(Glad)

add_library(glad include/glad/glad.h src/glad.c include/rg/Shader.h include/rg/Error.h)
target_include_directories(glad PUBLIC include/)