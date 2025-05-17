cmake_minimum_required(VERSION 3.14)
project(lab05 LANGUAGES CXX)

add_subdirectory(banking)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    add_subdirectory(tests)
endif()
