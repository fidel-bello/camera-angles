cmake_minimum_required(VERSION 3.13)
project(camera_hack)
set(CMAKE_CXX_STANDARD  14)
add_executable(camera_hack src/main.cpp src/hack_file/camera_hack.h src/hack_file/camera_hack.cpp src/hack_file/controller/controller.h)