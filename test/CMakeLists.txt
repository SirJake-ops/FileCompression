cmake_minimum_required(VERSION 3.30)
project(FileCompressionProjectTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS iostreams)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} ${BZIP2_INCLUDE_DIR} ${HEADERS_DIR})

enable_testing()

add_executable(FileCompressionProjectTest
        LoadDataTests.cpp
        main_test.cpp
        ../headers/FileManipulation/LoadData.cpp
        ../headers/FileManipulation/FileData.cpp
        FileDataTests.cpp
        ThreadPoolTests.cpp
        ../headers/ThreadFunctionality/ThreadPool.cpp
        ../headers/ThreadFunctionality/ThreadPool.h
        ../headers/ThreadFunctionality/ThreadPoolInterface.h
)

target_link_libraries(FileCompressionProjectTest gtest gtest_main gmock gmock_main ${Boost_LIBRARIES} z)
include(GoogleTest)
gtest_discover_tests(FileCompressionProjectTest)