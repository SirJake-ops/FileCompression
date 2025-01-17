cmake_minimum_required(VERSION 3.30)
project(ImGui)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/*.h
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC ${IMGUI_DIR})