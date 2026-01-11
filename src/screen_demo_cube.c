/**********************************************************************************************
*
*   raylib - Cube Demo Screen
*
*   Demonstrates 3D cube drawing
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include <math.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static Camera3D camera = { 0 };
static Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
static Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };
static float cubeRotation = 0.0f;

//----------------------------------------------------------------------------------
// Cube Demo Screen Functions Definition
//----------------------------------------------------------------------------------

// Cube Demo Screen Initialization logic
void InitCubeDemoScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    cubeRotation = 0.0f;
    
    // Setup camera
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

// Cube Demo Screen Update logic
void UpdateCubeDemoScreen(void)
{
    framesCounter++;
    
    // Rotate cube
    cubeRotation += 1.0f;
    if (cubeRotation >= 360.0f) cubeRotation = 0.0f;
    
    // Rotate camera around cube
    float cameraAngle = framesCounter * 0.02f;
    camera.position.x = cosf(cameraAngle) * 10.0f;
    camera.position.z = sinf(cameraAngle) * 10.0f;
    
    // Press ESC to go back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Cube Demo Screen Draw logic
void DrawCubeDemoScreen(void)
{
    ClearBackground(RAYWHITE);
    
    // Draw title (2D)
    DrawText("CUBE DEMO (3D)", 20, 20, 40, DARKGRAY);
    
    // Draw 3D content
    BeginMode3D(camera);
    
        DrawCubeV(cubePosition, cubeSize, RED);
        DrawCubeWiresV(cubePosition, cubeSize, MAROON);
        
        // Draw grid for reference
        DrawGrid(10, 1.0f);
        
    EndMode3D();
    
    // Draw instructions (2D)
    DrawText("Press ESC to return to menu", 20, GetScreenHeight() - 40, 20, DARKGRAY);
}

// Cube Demo Screen Unload logic
void UnloadCubeDemoScreen(void)
{
    // Unload screen variables here (if any)
}

// Cube Demo Screen should finish?
int FinishCubeDemoScreen(void)
{
    return finishScreen;
}
