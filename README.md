# fiNESse

### Work in Progress

This is my first attempt at writing an emulator.
I want to use this as an opportunity to practice my software development skills and learn about hardware emulation.
The goal is to write a working NES emulator in C++.

## Build System

This project uses the [meson](https://mesonbuild.com/) build system.
See the [installation instructions](https://mesonbuild.com/SimpleStart.html) in the meson documentation.

To build and run, enter the following commands:

```
meson build
ninja -C build
./build/src/finesse <filename>.nes
```
