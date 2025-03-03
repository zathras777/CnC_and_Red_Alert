cmake_minimum_required(VERSION 3.10)
project(CnCRedAlert)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# -Wno-changes-meaning/-Wnarrowing to compile, others for noise
add_compile_options(-Wno-error=changes-meaning -Wno-error=narrowing -Wno-write-strings)

add_subdirectory(port)
add_subdirectory(SDLLIB)

add_subdirectory(CODE)