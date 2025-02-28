cmake_minimum_required(VERSION 3.10)
project(CnCRedAlert)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wno-changes-meaning)

add_subdirectory(CODE)