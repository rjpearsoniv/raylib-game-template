/**********************************************************************************************
*
*   raylib - Circle Demo Screen
*
*   Demonstrates 2D circle drawing
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
static Vector2 circlePosition;
static float circleRadius = 50.0f;
static Color circleColor = BLUE;

//----------------------------------------------------------------------------------
// Circle Demo Screen Functions Definition
//----------------------------------------------------------------------------------

// Circle Demo Screen Initialization logic
void InitCircleDemoScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    circlePosition = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

// Circle Demo Screen Update logic
void UpdateCircleDemoScreen(void)
{
    framesCounter++;
    
    // Animate circle
    circleRadius = 50.0f + sinf(framesCounter * 0.05f) * 20.0f;
    
    // Change color over time
    circleColor.r = (unsigned char)(127 + sinf(framesCounter * 0.02f) * 127);
    circleColor.g = (unsigned char)(127 + sinf(framesCounter * 0.03f) * 127);
    circleColor.b = (unsigned char)(127 + sinf(framesCounter * 0.04f) * 127);
    
    // Press ESC to go back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Circle Demo Screen Draw logic
void DrawCircleDemoScreen(void)
{
    ClearBackground(RAYWHITE);
    
    // Draw title
    DrawText("CIRCLE DEMO", 20, 20, 40, DARKGRAY);
    
    // Draw the animated circle
    DrawCircleV(circlePosition, circleRadius, circleColor);
    DrawCircleLines((int)circlePosition.x, (int)circlePosition.y, (int)circleRadius, DARKGRAY);
    
    // Draw instructions
    DrawText("Press ESC to return to menu", 20, GetScreenHeight() - 40, 20, DARKGRAY);
}

// Circle Demo Screen Unload logic
void UnloadCircleDemoScreen(void)
{
    // Unload screen variables here (if any)
}

// Circle Demo Screen should finish?
int FinishCircleDemoScreen(void)
{
    return finishScreen;
}
