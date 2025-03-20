cmake_minimum_required(VERSION 3.12)
project(CnCRedAlert)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(
        /wd4996 # yes, this code is old and uses "unsafe" functions
        /wd4068 /wd4081 # old #pragmas for another compiler
        /wd4661 # missing template definitions, 10000s of these
    )
else()
    # -Wnarrowing to compile, others for noise
    add_compile_options(-Wno-error=narrowing -Wno-write-strings)
    if(!APPLE)
        # -Wno-changes-meaning generates warnings on Mac
        add_compile_options(-Wno-error=changes-meaning)
    endif()
    # workarounds
    add_compile_definitions(-D__cdecl= -D__far= -D__stdcall= -Dcdecl= -Dfar=)
endif()

add_compile_definitions(-DWIN32) # hopefully easier than DOS


add_subdirectory(port)
add_subdirectory(SDLLIB)
add_subdirectory(WINVQ)

add_subdirectory(RA)
add_subdirectory(TD)
