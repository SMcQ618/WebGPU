cmake_minimum_required(VERSION 3.29)
project(GLSL_WebGPU)

set(CMAKE_CXX_STANDARD 17)

add_executable(GLSL_WebGPU main.cpp
        WebGPU/ray.h WebGPU/optix7.h WebGPU/scene.h WebGPU/sphere.h
        shader.glsl)
