add_executable(mixfile)

target_include_directories(mixfile PRIVATE "../../RA")
target_link_libraries(mixfile tech)

target_sources(mixfile PRIVATE 
    MIXFILE.CPP
    file_fn.cpp
)
