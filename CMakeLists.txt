cmake_minimum_required(VERSION 3.28.3)
project(Nerd2D)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the library as a shared library")
set(CPM_DOWNLOAD_LOCATION ${CMAKE_BINARY_DIR}/CPM.cmake)

file(DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/cpm.cmake
    ${CPM_DOWNLOAD_LOCATION})

include(${CPM_DOWNLOAD_LOCATION})

file(GLOB ENGINE_SRC src/*.cpp)

CPMAddPackage(
    NAME sdl
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
    GIT_TAG SDL2)

CPMAddPackage(
    NAME imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui"
    GIT_TAG master)

add_executable(Nerd2D ${ENGINE_SRC})

add_library(imgui
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp)

include_directories(
    ${sdl_SOURCE_DIR}/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${imgui_SOURCE_DIR}/misc/cpp)

target_link_libraries(imgui SDL2::SDL2)
target_link_libraries(Nerd2D SDL2::SDL2 imgui)
