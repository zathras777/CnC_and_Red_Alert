add_library(sdllib STATIC
    stub.cpp
)
target_include_directories(sdllib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)