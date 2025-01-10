#include "raylib.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // rectanlge dimensions
    const int rectWidth{50};
    const int rectHeight{80};    

    int posY{windowHeight - rectHeight};
    int velocity{0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables here
        //----------------------------------------------------------------------------------
        posY += velocity;

        // Draw
        //----------------------------------------------------------------------------------
        DrawRectangle(windowWidth / 2, posY, rectWidth, rectHeight, BLUE);
        
        // draw main window
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (IsKeyPressed(KEY_SPACE)) {
            velocity -= 10;
        }

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}