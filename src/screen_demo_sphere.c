/**********************************************************************************************
*
*   raylib - Sphere Demo Screen
*
*   Demonstrates 3D sphere drawing
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
static Vector3 spherePosition = { 0.0f, 0.0f, 0.0f };
static float sphereRadius = 2.0f;

//----------------------------------------------------------------------------------
// Sphere Demo Screen Functions Definition
//----------------------------------------------------------------------------------

// Sphere Demo Screen Initialization logic
void InitSphereDemoScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    
    // Setup camera
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

// Sphere Demo Screen Update logic
void UpdateSphereDemoScreen(void)
{
    framesCounter++;
    
    // Rotate camera around sphere
    float cameraAngle = framesCounter * 0.02f;
    camera.position.x = cosf(cameraAngle) * 10.0f;
    camera.position.z = sinf(cameraAngle) * 10.0f;
    
    // Press ESC to go back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
        if (soundEnabled) PlaySound(fxCoin);
    }
}

// Sphere Demo Screen Draw logic
void DrawSphereDemoScreen(void)
{
    ClearBackground(RAYWHITE);
    
    // Draw title (2D)
    DrawText("SPHERE DEMO (3D)", 20, 20, 40, DARKGRAY);
    
    // Draw 3D content
    BeginMode3D(camera);
    
        DrawSphere(spherePosition, sphereRadius, BLUE);
        DrawSphereWires(spherePosition, sphereRadius, 16, 16, DARKBLUE);
        
        // Draw grid for reference
        DrawGrid(10, 1.0f);
        
    EndMode3D();
    
    // Draw instructions (2D)
    DrawText("Press ESC to return to menu", 20, GetScreenHeight() - 40, 20, DARKGRAY);
}

// Sphere Demo Screen Unload logic
void UnloadSphereDemoScreen(void)
{
    // Unload screen variables here (if any)
}

// Sphere Demo Screen should finish?
int FinishSphereDemoScreen(void)
{
    return finishScreen;
}
