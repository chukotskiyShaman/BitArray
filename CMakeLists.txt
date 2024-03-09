cmake_minimum_required(VERSION 3.22)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    googletest.cpp
    bitarray.cpp
)

add_executable(lab1 ${SOURCES})

target_link_libraries(lab1 gtest)
