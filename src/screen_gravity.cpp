/**********************************************************************************************
*
*   raylib - Gravity Simulation Screen
*
*   3D gravity simulation with N-body physics
*
**********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "screens.h"
#include <vector>
#include <cmath>
#include <iostream>

//----------------------------------------------------------------------------------
// Constants and Global Variables
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

const double G = 6.6743e-11; // gravitational constant m^3 kg^-1 s^-2
const float sizeRatio = 30000.0f;
static bool paused = true;
static Camera3D camera = { 0 };

//----------------------------------------------------------------------------------
// GravityObject class
//----------------------------------------------------------------------------------
class GravityObject {
public:
    Vector3 position;
    Vector3 velocity;
    float mass;
    float density;
    float radius;
    Color color;
    bool glow;
    bool initializing;

    GravityObject(Vector3 pos, Vector3 vel, float m, float d = 5515.0f, Color col = BLUE, bool glowing = false) {
        position = pos;
        velocity = vel;
        mass = m;
        density = d;
        color = col;
        glow = glowing;
        initializing = false;
        UpdateRadius();
    }

    void UpdateRadius() {
        // Calculate radius from mass and density: V = (4/3)πr³ = m/ρ
        float volume = mass / density;
        radius = powf((3.0f * volume) / (4.0f * PI), 1.0f / 3.0f) / sizeRatio;
    }

    void UpdatePosition(float deltaTime) {
        // Scale down movement for visualization
        position.x += velocity.x * deltaTime / 94.0f;
        position.y += velocity.y * deltaTime / 94.0f;
        position.z += velocity.z * deltaTime / 94.0f;
    }

    void Accelerate(float ax, float ay, float az) {
        velocity.x += ax;
        velocity.y += ay;
        velocity.z += az;
    }

    void Draw() {
        if (glow) {
            // Draw glowing sun-like object
            DrawSphere(position, radius * 1.2f, Fade(color, 0.5f));
        }
        DrawSphere(position, radius, color);
        DrawSphereWires(position, radius, 8, 8, Fade(color, 0.3f));
    }

    float CheckCollision(const GravityObject& other) {
        float dx = other.position.x - position.x;
        float dy = other.position.y - position.y;
        float dz = other.position.z - position.z;
        float distance = sqrtf(dx * dx + dy * dy + dz * dz);
        
        if (distance < (radius + other.radius)) {
            return 0.5f; // Damping factor on collision
        }
        return 1.0f;
    }
};

static std::vector<GravityObject> objects;

//----------------------------------------------------------------------------------
// Gravity Simulation Screen Functions
//----------------------------------------------------------------------------------

void InitGravityScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    paused = true;
    
    // Setup camera
    camera.position = (Vector3){ 0.0f, 1000.0f, 5000.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    // Clear previous objects
    objects.clear();
    
    // Create initial objects - binary star system with central massive object
    objects.push_back(GravityObject(
        (Vector3){-5000.0f, 650.0f, -350.0f}, 
        (Vector3){0.0f, 0.0f, 1500.0f}, 
        5.97219f * powf(10, 22), 
        5515.0f, 
        SKYBLUE, 
        false
    ));
    
    objects.push_back(GravityObject(
        (Vector3){5000.0f, 650.0f, -350.0f}, 
        (Vector3){0.0f, 0.0f, -1500.0f}, 
        5.97219f * powf(10, 22), 
        5515.0f, 
        SKYBLUE, 
        false
    ));
    
    // Central massive object (sun-like)
    objects.push_back(GravityObject(
        (Vector3){0.0f, 0.0f, -350.0f}, 
        (Vector3){0.0f, 0.0f, 0.0f}, 
        1.989f * powf(10, 25), 
        5515.0f, 
        YELLOW, 
        true
    ));
}

void UpdateGravityScreen(void)
{
    framesCounter++;
    float deltaTime = GetFrameTime();
    
    // Camera controls
    if (IsKeyDown(KEY_W)) camera.position.z -= 100.0f;
    if (IsKeyDown(KEY_S)) camera.position.z += 100.0f;
    if (IsKeyDown(KEY_A)) camera.position.x -= 100.0f;
    if (IsKeyDown(KEY_D)) camera.position.x += 100.0f;
    if (IsKeyDown(KEY_Q)) camera.position.y -= 100.0f;
    if (IsKeyDown(KEY_E)) camera.position.y += 100.0f;
    
    // Toggle pause with SPACE
    if (IsKeyPressed(KEY_SPACE)) {
        paused = !paused;
        if (soundEnabled) PlaySound(fxCoin);
    }
    
    // Reset simulation with R
    if (IsKeyPressed(KEY_R)) {
        InitGravityScreen();
        if (soundEnabled) PlaySound(fxCoin);
    }
    
    if (!paused) {
        // Calculate gravitational forces
        for (size_t i = 0; i < objects.size(); i++) {
            for (size_t j = 0; j < objects.size(); j++) {
                if (i == j || objects[i].initializing || objects[j].initializing) continue;
                
                float dx = objects[j].position.x - objects[i].position.x;
                float dy = objects[j].position.y - objects[i].position.y;
                float dz = objects[j].position.z - objects[i].position.z;
                float distance = sqrtf(dx * dx + dy * dy + dz * dz);
                
                if (distance > 0.1f) {
                    // Normalize direction
                    float dirX = dx / distance;
                    float dirY = dy / distance;
                    float dirZ = dz / distance;
                    
                    // Convert distance to meters for physics calculation
                    double distanceMeters = distance * 1000.0;
                    
                    // F = G * m1 * m2 / r²
                    double force = (G * objects[i].mass * objects[j].mass) / (distanceMeters * distanceMeters);
                    
                    // a = F / m
                    float acceleration = (float)(force / objects[i].mass);
                    
                    // Apply acceleration
                    objects[i].Accelerate(
                        dirX * acceleration,
                        dirY * acceleration,
                        dirZ * acceleration
                    );
                    
                    // Check collision
                    float damping = objects[i].CheckCollision(objects[j]);
                    objects[i].velocity.x *= damping;
                    objects[i].velocity.y *= damping;
                    objects[i].velocity.z *= damping;
                }
            }
        }
        
        // Update positions
        for (auto& obj : objects) {
            if (!obj.initializing) {
                obj.UpdatePosition(deltaTime);
            }
        }
    }
    
    // Update camera target to center of mass
    Vector3 centerOfMass = {0};
    float totalMass = 0;
    for (const auto& obj : objects) {
        if (!obj.initializing) {
            centerOfMass.x += obj.position.x * obj.mass;
            centerOfMass.y += obj.position.y * obj.mass;
            centerOfMass.z += obj.position.z * obj.mass;
            totalMass += obj.mass;
        }
    }
    if (totalMass > 0) {
        camera.target.x = centerOfMass.x / totalMass;
        camera.target.y = centerOfMass.y / totalMass;
        camera.target.z = centerOfMass.z / totalMass;
    }
    
    // ESC to return to menu
    if (IsKeyPressed(KEY_ESCAPE)) {
        finishScreen = 1;
        if (soundEnabled) PlaySound(fxCoin);
    }
}

void DrawGravityScreen(void)
{
    ClearBackground(BLACK);
    
    BeginMode3D(camera);
    
        // Draw grid
        DrawGrid(100, 1000.0f);
        
        // Draw all gravity objects
        for (auto& obj : objects) {
            obj.Draw();
        }
        
    EndMode3D();
    
    // Draw UI
    DrawText("GRAVITY SIMULATION", 20, 20, 40, WHITE);
    DrawText(paused ? "PAUSED" : "RUNNING", 20, 70, 30, paused ? RED : GREEN);
    
    // Instructions
    DrawText("SPACE: Pause/Resume | R: Reset | WASDQE: Move Camera", 20, GetScreenHeight() - 80, 20, LIGHTGRAY);
    DrawText("ESC: Return to Menu", 20, GetScreenHeight() - 50, 20, LIGHTGRAY);
    
    // Object count
    DrawText(TextFormat("Objects: %d", (int)objects.size()), GetScreenWidth() - 200, 20, 20, WHITE);
}

void UnloadGravityScreen(void)
{
    objects.clear();
}

int FinishGravityScreen(void)
{
    return finishScreen;
}
