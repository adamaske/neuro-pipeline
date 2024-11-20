cmake_minimum_required(VERSION 3.16)

project(NeuroPipeline VERSION 0.1 LANGUAGES CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)



set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resources")

file(GLOB_RECURSE INCS "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE SRCS "${SOURCE_DIR}/*.cpp")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# QT
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} "${CMAKE_CURRENT_SOURCE_DIR}/Forms")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Qml)


add_subdirectory(Vendor)
configure_file("${RESOURCES_DIR}/Config.h.in" "${INCLUDE_DIR}/Config.h")


qt_standard_project_setup()
qt_add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE 
"${CMAKE_CURRENT_SOURCE_DIR}/Include" 
"${CMAKE_CURRENT_SOURCE_DIR}/Forms"
${Python_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PRIVATE ${Python_LIBRARY_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE 
Vendor 
Qt6::Core 
Qt6::Widgets 
Qt6::Gui
Qt6::Qml
compiler_flags 
)

install(DIRECTORY ${RESOURCES_DIR} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})