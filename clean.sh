#!/bin/bash
# Clean build artifacts for Linux/Unix

echo "Cleaning build artifacts..."

# Clean game
cd src
make clean
rm -f *.o raylib_game
cd ..

# Clean raylib if it exists
if [ -f "../raylib/src/libraylib.a" ]; then
    echo "Cleaning raylib library..."
    cd ../raylib/src
    make clean
    cd ../../raylib-game-template
fi

echo "Clean complete!"
