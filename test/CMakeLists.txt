cmake_minimum_required(VERSION 3.30)
project(FileCompressionProjectTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(FileCompressionProjectTest
        hello_test.cpp
        LoadDataTests.cpp
        main_test.cpp
        ../FileManipulation/LoadData.cpp
        ../FileManipulation/FileData.cpp
        FileDataTests.cpp
)

target_link_libraries(FileCompressionProjectTest gtest gtest_main gmock gmock_main)
include(GoogleTest)
gtest_discover_tests(FileCompressionProjectTest)