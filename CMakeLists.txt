cmake_minimum_required(VERSION 3.15)

project(NeuroPipeline VERSION 0.1)


add_library(project_compiler_definitions INTERFACE)


configure_file(Config.h.in "${CMAKE_CURRENT_SOURCE_DIR}/Include/Config.h")

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp")