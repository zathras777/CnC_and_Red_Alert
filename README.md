
# Command & Conquer / Red Alert SDL

This repository is a fork of https://github.com/electronicarts/CnC_Red_Alert, partially merged with https://github.com/electronicarts/CnC_Tiberian_Dawn. It builds more portable, somewhat functional versions of both games.

## Dependencies

All this fork needs to compile is:

- A C++ compiler
- CMake
- SDL2


## Compiling (Everywhere)

1. `cmake -Bbuild`
2. `cmake --build build`
3. Find some data files
4. Run `tdsdl` or `rasdl`
5. (optional) Command and/or conquer

## Status

Both games compile on Linux/macOS/Windows and run at least to the menus. I have lightly tested a few campain missions, RA is more stable than TD.

There's some support for network multiplayer in RA. (I've successfully tested one game between Linux/Windows.)

Code only used by later missions is likely still broken, or possibly missing entirely if it's part of something I had to translate from assembly.

## Original README

[Over here](README-EA.md)

