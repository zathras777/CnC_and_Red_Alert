add_library(port STATIC
    ddraw.cpp
    dos.cpp
    mpeg.cpp
    string.cpp
    windows.cpp
)

target_include_directories(port PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_definitions(port PUBLIC PORTABLE=1)