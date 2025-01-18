cmake_minimum_required(VERSION 3.30)
project(FileCompressionProject)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS system iostreams)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} ${BZIP2_INCLUDE_DIR})

add_executable(FileCompressionProject main.cpp
    FileManipulation/FileData.cpp
    FileManipulation/FileData.h
    FileManipulation/LoadData.cpp
    FileManipulation/LoadData.h
    external/ImGuiFileDialog/ImGuiFileDialog.cpp
    FileManipulation/FileManipulationHelperMethod.h
)

add_subdirectory(external)
add_subdirectory(test)

target_include_directories(FileCompressionProject PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/external/imgui)
target_link_libraries(FileCompressionProject PRIVATE ${BZIP2_LIBRARIES} imgui glfw OpenGL::GL ${Boost_LIBRARIES} Boost::iostreams)