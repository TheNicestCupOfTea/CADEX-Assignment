# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

cmake_minimum_required (VERSION 3.8)
project ("CADEX Assignment v4")

# Включите подпроекты.
add_subdirectory ("CADEX Assignment v4")
