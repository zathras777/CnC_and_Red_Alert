add_library(port STATIC
    string.cpp
)

target_include_directories(port PUBLIC ${CMAKE_CURRENT_LIST_DIR})