#!/bin/bash
# Build script for Linux/Unix

echo "Building raylib game for Linux..."

# Check if raylib exists
if [ ! -d "../raylib/src" ]; then
    echo "ERROR: raylib not found at ../raylib/src"
    echo "Please clone raylib: git clone https://github.com/raysan5/raylib.git"
    echo "Place it next to raylib-game-template folder"
    exit 1
fi

# Build raylib first if not already built
if [ ! -f "../raylib/src/libraylib.a" ]; then
    echo "Building raylib library..."
    cd ../raylib/src
    make PLATFORM=PLATFORM_DESKTOP
    cd ../../raylib-game-template
fi

# Build the game
cd src
make PLATFORM=PLATFORM_DESKTOP
cd ..

echo ""
echo "Build complete! Run the game with: ./src/raylib_game"
