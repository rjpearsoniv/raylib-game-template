@echo off
REM Build script for Windows using w64devkit

echo Building raylib game for Windows...

REM Add w64devkit to PATH
set PATH=C:\w64devkit\bin;%PATH%

REM Check if raylib exists
if not exist "..\raylib\src" (
    echo ERROR: raylib not found at ..\raylib\src
    echo Please clone raylib: git clone https://github.com/raysan5/raylib.git
    echo Place it next to raylib-game-template folder
    exit /b 1
)

REM Build raylib first if not already built
if not exist "..\raylib\src\libraylib.a" (
    echo Building raylib library...
    cd ..\raylib\src
    mingw32-make PLATFORM=PLATFORM_DESKTOP
    cd ..\..\raylib-game-template
)

REM Build the game
cd src
mingw32-make PLATFORM=PLATFORM_DESKTOP
cd ..

echo.
echo Build complete! Run the game with: src\raylib_game.exe
