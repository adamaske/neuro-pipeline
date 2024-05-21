cmake_minimum_required(VERSION 3.16)

project(NeuroPipeline VERSION 0.1)

add_library(project_compiler_definitions INTERFACE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE "Debug")
configure_file(Config.h.in "${CMAKE_CURRENT_SOURCE_DIR}/Include/Config.h")

file(GLOB INCS "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h")
file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
add_subdirectory(Vendor)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} "${CMAKE_CURRENT_SOURCE_DIR}/Forms")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_executable(${PROJECT_NAME}
"Source/main.cpp" 
"Source/NeuroPipeline.cpp"
"Source/Files.cpp" 
"Source/Pipeline.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE 
"${CMAKE_CURRENT_SOURCE_DIR}/Include" 
"${CMAKE_CURRENT_SOURCE_DIR}/Forms"
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
Vendor  
Qt6::Core 
Qt6::Widgets
)