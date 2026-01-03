@echo off
REM Clean build artifacts for Windows

echo Cleaning build artifacts...

set PATH=C:\w64devkit\bin;%PATH%

REM Clean game
cd src
mingw32-make clean
del /Q *.o *.exe 2>nul
cd ..

REM Clean raylib if it exists
if exist "..\raylib\src\libraylib.a" (
    echo Cleaning raylib library...
    cd ..\raylib\src
    mingw32-make clean
    cd ..\..\raylib-game-template
)

echo Clean complete!
