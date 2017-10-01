# Lockscr
### Simple linux lockscreen to practice cmake usage

## Dependencies:
* Cairo
* XCB
* X11

## Build 
To build this repository, you will need to use CMake.
Preferably, create a directory for an out-of-source build:

    mkdir build

Move into the directory, and initiate cmake:

    cd build && cmake ..

Then build the actual binary via the generated Makefile:

    make

The binary will be located in the `src/` folder. 

## Usage
To use the lockscreen, use:

    ./lockscr [bg-path]




