#include "raylib.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    const int gravity{1}; // acceleration due to gravity (pixels/frame)/frame

    // rectanlge dimensions
    const int rectWidth{50};
    const int rectHeight{80};

    // is the rectangle in the air?
    bool isInAir{};   
    // jump velocity
    const int jumpVel{-22}; 

    int posY{windowHeight - rectHeight};
    int velocity{0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Draw
        //----------------------------------------------------------------------------------
        DrawRectangle(windowWidth / 2, posY, rectWidth, rectHeight, BLUE);
        
        // draw main window
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ground check - stop falling when we hit the ground
        if (posY >= windowHeight - rectHeight)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else 
        {
            // rectangle is in the air
            velocity += gravity;
            isInAir = true;
        }
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }

        // Update
        //----------------------------------------------------------------------------------
        posY += velocity; // update position with new velocity
        //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}