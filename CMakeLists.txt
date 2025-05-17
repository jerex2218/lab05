cmake_minimum_required(VERSION 3.14)
project(lab05 LANGUAGES CXX)

# Подключаем библиотеку banking
add_subdirectory(banking)

# Подключаем тесты (только если это основной проект)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(tests)
endif()
