# Raylib Game Template - Command Line Build

This template provides easy command-line building for both Windows and Linux.

## Quick Start

### Prerequisites

**Windows:**
- [w64devkit](https://github.com/skeeto/w64devkit) installed at `C:\w64devkit`
- Git (to clone raylib)

**Linux:**
- GCC compiler and make
- Required libraries: `libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev`
  ```bash
  sudo apt-get install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
  ```

### Setup

1. Clone raylib alongside this template:
   ```bash
   cd ..
   git clone https://github.com/raysan5/raylib.git
   cd raylib-game-template
   ```

   Your directory structure should be:
   ```
   parent-directory/
   ├── raylib/
   └── raylib-game-template/
   ```

### Building

**Windows:**
```cmd
build.bat
```

**Linux:**
```bash
./build.sh
```

The first build will compile raylib (takes a few minutes). Subsequent builds are faster.

### Running

**Windows:**
```cmd
run.bat
```

**Linux:**
```bash
./run.sh
```

Or run directly:
- Windows: `src\raylib_game.exe`
- Linux: `./src/raylib_game`

### Cleaning

**Windows:**
```cmd
clean.bat
```

**Linux:**
```bash
./clean.sh
```

## Manual Build

If you prefer to build manually:

**Windows:**
```cmd
cd src
mingw32-make
```

**Linux:**
```bash
cd src
make
```

## Build Modes

By default, builds are in RELEASE mode. For debug builds:

**Windows:**
```cmd
cd src
mingw32-make BUILD_MODE=DEBUG
```

**Linux:**
```bash
cd src
make BUILD_MODE=DEBUG
```

## Troubleshooting

**Windows: "mingw32-make not found"**
- Make sure w64devkit is installed at `C:\w64devkit`
- Or update the `COMPILER_PATH` in `src/Makefile`

**Windows: "raylib not found"**
- Clone raylib next to this template directory (see Setup above)

**Linux: Compilation errors**
- Make sure all development libraries are installed (see Prerequisites)
- Try `make clean` before rebuilding

## Additional Build Options

The project also includes:
- **CMake build**: See main README.md
- **Visual Studio**: Use `projects/VS2022/raylib-game-template.sln`
