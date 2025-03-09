cmake_minimum_required(VERSION 3.10)
project(CnCRedAlert)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    # -Wno-changes-meaning/-Wnarrowing to compile, others for noise
    add_compile_options(-Wno-error=changes-meaning -Wno-error=narrowing -Wno-write-strings)
endif()

add_compile_definitions(-DWIN32) # hopefully easier than DOS

# workarounds
add_compile_definitions(-D__cdecl= -D__far= -D__stdcall= -Dcdecl= -Dfar=)

add_subdirectory(port)
add_subdirectory(SDLLIB)
add_subdirectory(WINVQ)

add_subdirectory(CODE)