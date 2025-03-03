add_library(sdllib STATIC
    audio.cpp
    buffer.cpp
    dipthong.cpp
    drawbuff.cpp
    font.cpp
    iconcach.cpp
    iff.cpp
    keyboard.cpp
    mem.cpp
    misc.cpp
    mouse.cpp
    palette.cpp
    playcd.cpp
    shape.cpp
    tile.cpp
    timer.cpp
    wincomm.cpp
    window.cpp
    wsa.cpp
)
target_include_directories(sdllib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# FIXME: avoid needing this
target_include_directories(sdllib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../port)


find_package(SDL2 REQUIRED)
target_link_libraries(sdllib SDL2::SDL2)