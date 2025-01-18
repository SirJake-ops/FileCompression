cmake_minimum_required(VERSION 3.30)
project(ImGui)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB IMGUI_SOURCES
        imgui.cpp
        imgui_draw.cpp
        imgui_demo.cpp
        imgui_widgets.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC ${IMGUI_DIR})