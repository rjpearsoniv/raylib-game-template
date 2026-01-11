@echo off
REM Build script for Windows using w64devkit (DEBUG MODE)

echo Building raylib game for Windows - DEBUG with symbols...

REM Add w64devkit to PATH
set PATH=C:\w64devkit\bin;%PATH%

REM Check if raylib exists
if not exist "..\raylib\src" (
    echo ERROR: raylib not found at ..\raylib\src
    echo Please clone raylib: git clone https://github.com/raysan5/raylib.git
    echo Place it next to raylib-game-template folder
    exit /b 1
)

REM Build raylib first if not already built (DEBUG mode)
if not exist "..\raylib\src\libraylib.a" (
    echo Building raylib library - DEBUG mode...
    cd ..\raylib\src
    mingw32-make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=DEBUG
    cd ..\..\raylib-game-template
)

REM Build the game in DEBUG mode
cd src
mingw32-make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=DEBUG
cd ..

echo.
echo Debug build complete! Debug executable: src\raylib_game.exe
echo Use VSCode debugger [F5] to run with breakpoints.
