# Usage
## Running
Simply running the executable opens up a window where the dungeon generation is visualized. Pressing the right arrow button advances the generation to the next step. At the end of the generation, the fully generated dungeon is printed into the console in json format.

Running the executable with `--headless` option runs the dungeon generation through in all in one go and prints out the result into the console in json format.

## Building

This project uses [CMake](https://cmake.org/) for building. The project has been tested to build with GCC 10 (Linux and MinGW) and MSVC 19.16 (Windows). 

Building the Linux version requires at least the following packages:
- [simple2d](https://github.com/simple2d/simple2d)
- libglew-dev
- libsdl2-dev
- libsdl2-image-dev
- libsdl2-mixer-dev
- libsdl2-ttf-dev
- libegl1-mesa-dev
- libgles2-mesa-dev

After the dependencies are satisfied, building the project should work with the following commands:

    cmake .
    make

If you're having problems building the project, taking a look at [travis.yml](https://github.com/mikaelfr/dungeon-generation-tiralab/blob/master/.travis.yml) might help.

## Installation

Prebuilt binaries are available in releases for Windows and Linux. Windows version is tested on Windows 10 x64 and Linux version on Xubuntu 20.04. The Windows version is contained in dungeon_generator.zip and the Linux versions are dungeon_generator and dungeon_generator_test. 

The Linux version requires at least the following packages:

* libsdl2-2.0
* libsdl2-image-dev
* libsdl2-mixer-dev
* libsdl2-ttf-dev

If you're having trouble with running the project, take a look at [travis.yml](https://github.com/mikaelfr/dungeon-generation-tiralab/blob/master/.travis.yml) for build steps.

## Troubleshooting

SDL was unable to create an OpenGL context. The version of OpenGL your graphics drivers support might be too old. I was unable to get the Linux version working in VirtualBox.

If SDL cannot find matching GLX visual on linux, take a look at [this](https://stackoverflow.com/questions/41338549/sdl2-cant-create-window-since-it-couldnt-find-matching-glx-visual).
