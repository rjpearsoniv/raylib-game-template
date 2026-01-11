The original pong game of 1973 covers many 
of the aspects to computer game programming.

1. Movement
2. Controls
3. Collision detection
4. Scoring
5. AI

Steps to develop pong. ( using divide and conquer)

1. Create a blank screen & Game loop.
2. Draw the paddles and the ball.
3. Move the ball around.
4. Check for a collision with all edges.
5. Move the players paddle.
6. Move the CPU paddle with AI.
7. Check for a collision with the paddles.
8. Add scoring.

Game structure

Definitions
- defining the variables needed
- creating the game objects

Game loop
- updating the positions of the game objects
- checking for collisions

Steps

Call InitWindow()
SetTargetFPS()
Call  CloseWindow()

Then write the GameLoop in the middle

while(WindowShouldClose() == false)
    BeginDrawing()

    EndDrawing()

STEP NUMBER 1 IS NOW DONE.

=================================================================================================

Window coordiantes

(0,0) is at the top left of the screen.

X increases going left to right
y increases going from from top to bottom




