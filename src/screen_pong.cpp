/**********************************************************************************************
*
*   raylib - Pong Game Screen
*
*   Pong game implementation as a demo screen
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

// Pong colors
static Color Green = Color{38, 185, 154, 255};
static Color Dark_Green = Color{20, 160, 133, 255};
static Color Light_Green = Color{129, 204, 184, 255};
static Color Yellow = Color{243, 213, 91, 255};

static int player_score = 0;
static int cpu_score = 0;

// Ball class
class Ball {
 public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle((int)x, (int)y, (float)radius, Yellow);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        // Cpu wins
        if (x + radius >= GetScreenWidth()) {
            cpu_score++;
            ResetBall();
        }

        if (x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = (float)(GetScreenWidth() / 2);
        y = (float)(GetScreenHeight() / 2);

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

// Paddle class
class Paddle {
 protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = (float)(GetScreenHeight() - height);
        }
    }

 public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8f, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        LimitMovement();
    }
};

// CPU Paddle class
class CpuPaddle : public Paddle {
 public:
    void Update(int ball_y){
        if (y + height / 2 > ball_y) {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y) {
            y = y + speed;
        }
        LimitMovement();
    }
};

static Ball ball;
static Paddle player;
static CpuPaddle cpu;

//----------------------------------------------------------------------------------
// Pong Screen Functions Definition
//----------------------------------------------------------------------------------

// Pong Screen Initialization logic
void InitPongScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    player_score = 0;
    cpu_score = 0;
    
    // Initialize ball
    ball.radius = 20;
    ball.x = (float)(GetScreenWidth() / 2);
    ball.y = (float)(GetScreenHeight() / 2);
    ball.speed_x = 7;
    ball.speed_y = 7;

    // Initialize player paddle
    player.width = 25;
    player.height = 120;
    player.x = (float)(GetScreenWidth() - player.width - 10);
    player.y = (float)(GetScreenHeight() / 2 - player.height / 2);
    player.speed = 6;

    // Initialize CPU paddle
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = (float)(GetScreenHeight() / 2 - cpu.height / 2);
    cpu.speed = 6;
}

// Pong Screen Update logic
void UpdatePongScreen(void)
{
    framesCounter++;
    
    // Update game objects
    ball.Update();
    player.Update();
    cpu.Update((int)ball.y);

    // Check for collisions
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, (float)ball.radius, 
                                Rectangle{player.x, player.y, player.width, player.height})) {
        ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, (float)ball.radius, 
                                Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
        ball.speed_x *= -1;
    }
    
    // Press ESC to go back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        finishScreen = 1;
        if (soundEnabled) PlaySound(fxCoin);
    }
}

// Pong Screen Draw logic
void DrawPongScreen(void)
{
    ClearBackground(Dark_Green);
    
    // Draw pong court
    DrawRectangle(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), Green);
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 150, Light_Green);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
    
    // Draw game objects
    ball.Draw();
    cpu.Draw();
    player.Draw();
    
    // Draw scores
    DrawText(TextFormat("%i", cpu_score), GetScreenWidth() / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", player_score), 3 * GetScreenWidth() / 4 - 20, 20, 80, WHITE);
    
    // Draw instructions
    DrawText("Press ESC to return to menu", 20, GetScreenHeight() - 40, 20, WHITE);
}

// Pong Screen Unload logic
void UnloadPongScreen(void)
{
    // Unload pong screen variables here (if any)
}

// Pong Screen should finish?
int FinishPongScreen(void)
{
    return finishScreen;
}
