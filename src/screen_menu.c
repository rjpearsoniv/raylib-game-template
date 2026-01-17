/**********************************************************************************************
*
*   raylib - Menu Screen
*
*   Menu Screen Functions Definitions (Init, Update, Draw, Unload)
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

// Menu items
typedef enum {
    MENU_DRAW_CIRCLE = 0,
    MENU_DRAW_SQUARE,
    MENU_DRAW_SPHERE,
    MENU_DRAW_CUBE,
    MENU_PONG,
    MENU_GRAVITY,
    MENU_QUIT,
    MENU_ITEM_COUNT
} MenuItem;

static MenuItem selectedItem = MENU_DRAW_CIRCLE;

static const char* menuText[] = {
    "Draw Circle",
    "Draw Square",
    "Draw Sphere",
    "Draw Cube",
    "Pong Game",
    "Gravity Simulation",
    "Quit"
};

//----------------------------------------------------------------------------------
// Menu Screen Functions Definition
//----------------------------------------------------------------------------------

// Menu Screen Initialization logic
void InitMenuScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    selectedItem = MENU_DRAW_CIRCLE;
}

// Menu Screen Update logic
void UpdateMenuScreen(void)
{
    // Toggle sound with S key
    if (IsKeyPressed(KEY_S))
    {
        soundEnabled = !soundEnabled;
        if (soundEnabled) PlaySound(fxCoin);
    }
    
    // Navigate menu with UP/DOWN arrow keys
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedItem++;
        if (selectedItem >= MENU_ITEM_COUNT) selectedItem = 0;
        if (soundEnabled) PlaySound(fxCoin);
    }
    
    if (IsKeyPressed(KEY_UP))
    {
        selectedItem--;
        if (selectedItem < 0) selectedItem = MENU_ITEM_COUNT - 1;
        if (soundEnabled) PlaySound(fxCoin);
    }
    
    // Select item with ENTER or SPACE
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        // Return different values based on selected item
        // 1-4 map to demo screens, 5 is quit
        finishScreen = selectedItem + 1;
        if (soundEnabled) PlaySound(fxCoin);
    }
}

// Menu Screen Draw logic
void DrawMenuScreen(void)
{
    ClearBackground(RAYWHITE);
    
    // Draw title
    Vector2 titlePos = { 20, 20 };
    DrawTextEx(font, "RAYLIB MENU", titlePos, font.baseSize * 3.0f, 4, DARKBLUE);
    
    // Draw menu items
    int startY = 120;
    int itemHeight = 60;
    
    for (int i = 0; i < MENU_ITEM_COUNT; i++)
    {
        Color textColor = (i == selectedItem) ? ORANGE : DARKGRAY;
        Color bgColor = (i == selectedItem) ? (Color){255, 200, 0, 100} : (Color){200, 200, 200, 50};
        
        // Draw selection background
        if (i == selectedItem)
        {
            DrawRectangle(50, startY + i * itemHeight - 5, 700, 50, bgColor);
        }
        
        // Draw menu text
        Vector2 textPos = { 70, (float)(startY + i * itemHeight) };
        DrawTextEx(font, menuText[i], textPos, font.baseSize * 2.0f, 2, textColor);
        
        // Draw selection indicator
        if (i == selectedItem)
        {
            DrawText(">", 30, startY + i * itemHeight, 40, ORANGE);
        }
    }
    
    // Draw instructions
    DrawText("UP/DOWN: Navigate | ENTER/SPACE: Select | S: Toggle Sound", 20, 380, 18, DARKGRAY);
    
    // Draw sound status
    const char* soundStatus = soundEnabled ? "Sound: ON" : "Sound: OFF";
    Color soundColor = soundEnabled ? GREEN : RED;
    DrawText(soundStatus, 620, 20, 20, soundColor);
}

// Menu Screen Unload logic
void UnloadMenuScreen(void)
{
    // Unload menu screen variables here (if any)
}

// Menu Screen should finish?
int FinishMenuScreen(void)
{
    return finishScreen;
}
