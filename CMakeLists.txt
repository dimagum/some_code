cmake_minimum_required(VERSION 3.24)
project(lab_3_razbor)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_3_razbor main.cpp)

target_include_directories(lab_3_razbor PRIVATE ${CMAKE_SOURCE_DIR})
