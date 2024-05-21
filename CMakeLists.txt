cmake_minimum_required(VERSION 3.15)

project(NeuroPipeline VERSION 0.1)


add_library(project_compiler_definitions INTERFACE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

configure_file(Config.h.in "${CMAKE_CURRENT_SOURCE_DIR}/Include/Config.h")

file(GLOB INCS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h)
file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp )

add_executable(${PROJECT_NAME} 
"Source/main.cpp" 
"Source/NeuroPipeline.cpp" 
"Source/Files.cpp" 
"Source/Experiment.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Include")

add_subdirectory(Vendor)

target_link_libraries(${PROJECT_NAME} PRIVATE Vendor)