cmake_minimum_required(VERSION 3.30)
project(FileCompressionProject)

set(CMAKE_CXX_STANDARD 20)
set(Boost_DIR "${CMAKE_SOURCE_DIR}/external/boost")

set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/external/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} ${BZIP2_INCLUDE_DIR})

add_executable(FileCompressionProject main.cpp
        FileManipulation/FileData.cpp
        FileManipulation/FileData.h
        FileManipulation/LoadData.cpp
        FileManipulation/LoadData.h
        external/ImGuiFileDialog/ImGuiFileDialog.cpp
        external/imgui/imgui.cpp
        FileManipulation/FileManipulationHelperMethod.h
)

add_subdirectory(external)
add_subdirectory(test)
find_package(OpenGL REQUIRED)

target_include_directories(FileCompressionProject PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/external/imgui)
target_link_libraries(FileCompressionProject PRIVATE ${BZIP2_LIBRARIES} imgui glfw OpenGL::GL ${Boost_LIBRARIES})