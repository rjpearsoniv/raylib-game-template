/**********************************************************************************************
*
*   raylib - Kinematics Demo Screen
*
*   Physics simulation demonstrating different data structure layouts for performance
*   
*   Controls:
*   - ESC: Return to menu
*   - R: Toggle render bodies
*   - S: Toggle stats display
*   - U: Toggle update bodies
*   - 1-9,0: Set small body counts (1-10)
*   - Numpad 1-9,0: Set medium body counts (100K-1M)
*   - F1-F10: Set large body counts (1M-10M)
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "kinematics_App.h"

#include <memory>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static std::unique_ptr<App> kinematicsApp = nullptr;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Kinematics Screen Functions Definition
//----------------------------------------------------------------------------------

// Kinematics Screen Initialization logic
void InitKinematicsScreen(void)
{
    // Initialize the App with window dimensions and starting body count
    kinematicsApp = std::make_unique<App>(
        static_cast<float>(GetScreenWidth()), 
        static_cast<float>(GetScreenHeight()), 
        10 // Start with 10 bodies
    );
    
    finishScreen = 0;
}

// Kinematics Screen Update logic
void UpdateKinematicsScreen(void)
{
    if (kinematicsApp)
    {
        kinematicsApp->Update();
    }
    
    // Return to menu on ESC
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
    }
}

// Kinematics Screen Draw logic
void DrawKinematicsScreen(void)
{
    BeginDrawing();
    ClearBackground(BEIGE);
    
    if (kinematicsApp)
    {
        // Draw the simulation using the separated Draw() method
        kinematicsApp->Draw();
    }
    
    EndDrawing();
}

// Kinematics Screen Unload logic
void UnloadKinematicsScreen(void)
{
    // Destructor will be called automatically
    kinematicsApp.reset();
}

// Kinematics Screen should finish?
int FinishKinematicsScreen(void)
{
    return finishScreen;
}
