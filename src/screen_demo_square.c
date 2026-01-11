/**********************************************************************************************
*
*   raylib - Square Demo Screen
*
*   Demonstrates 2D rectangle/square drawing
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
static Rectangle square;
static float rotation = 0.0f;
static Color squareColor = RED;

//----------------------------------------------------------------------------------
// Square Demo Screen Functions Definition
//----------------------------------------------------------------------------------

// Square Demo Screen Initialization logic
void InitSquareDemoScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    square = (Rectangle){ GetScreenWidth() / 2.0f - 50, GetScreenHeight() / 2.0f - 50, 100, 100 };
    rotation = 0.0f;
}

// Square Demo Screen Update logic
void UpdateSquareDemoScreen(void)
{
    framesCounter++;
    
    // Rotate square
    rotation += 1.0f;
    if (rotation >= 360.0f) rotation = 0.0f;
    
    // Change color over time
    squareColor.r = (unsigned char)(127 + sinf(framesCounter * 0.02f) * 127);
    squareColor.g = (unsigned char)(127 + sinf(framesCounter * 0.03f) * 127);
    squareColor.b = (unsigned char)(127 + sinf(framesCounter * 0.04f) * 127);
    
    // Press ESC to go back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Square Demo Screen Draw logic
void DrawSquareDemoScreen(void)
{
    ClearBackground(RAYWHITE);
    
    // Draw title
    DrawText("SQUARE DEMO", 20, 20, 40, DARKGRAY);
    
    // Draw the rotating square
    Vector2 origin = { square.width / 2, square.height / 2 };
    Vector2 position = { square.x + origin.x, square.y + origin.y };
    DrawRectanglePro(square, origin, rotation, squareColor);
    DrawRectangleLinesEx((Rectangle){ square.x - origin.x, square.y - origin.y, square.width, square.height }, 2, DARKGRAY);
    
    // Draw instructions
    DrawText("Press ESC to return to menu", 20, GetScreenHeight() - 40, 20, DARKGRAY);
}

// Square Demo Screen Unload logic
void UnloadSquareDemoScreen(void)
{
    // Unload screen variables here (if any)
}

// Square Demo Screen should finish?
int FinishSquareDemoScreen(void)
{
    return finishScreen;
}
