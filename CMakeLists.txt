cmake_minimum_required(VERSION 3.30)
project(FileCompressionProject)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS_DIR "headers/")

find_package(Boost REQUIRED COMPONENTS system iostreams)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} ${BZIP2_INCLUDE_DIR} ${HEADERS_DIR})

file(GLOB_RECURSE HEADER_FILES "${HEADERS_DIR}/*.h")
file(GLOB_RECURSE SOURCE_FILES "${HEADERS_DIR}/*.cpp")

add_executable(FileCompressionProject
        main.cpp
        ${HEADER_FILES}
        ${SOURCE_FILES}
        external/ImGuiFileDialog/ImGuiFileDialog.cpp
)

add_subdirectory(external)
add_subdirectory(test)

target_include_directories(FileCompressionProject PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/external/imgui)
target_link_libraries(FileCompressionProject PRIVATE ${BZIP2_LIBRARIES} imgui glfw OpenGL::GL ${Boost_LIBRARIES} Boost::iostreams)