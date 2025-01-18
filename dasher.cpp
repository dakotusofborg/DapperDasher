#include "raylib.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    const int gravity{1'000}; // acceleration due to gravity (pixels/s)/s

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec;

    // scarfy variables 
    Texture2D  scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec; 
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0.0;
    scarfyRec.y = 0.0;
    Vector2 scarfyPos; // tracking scarfy's position
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int frame{}; // current animation frame

    // is the rectangle in the air?
    bool isInAir{};   
    // jump velocity
    const int jumpVel{-600}; // pixels/s

    int velocity{0};

    const float updateTime{1.0f / 12.0f}; // time for each frame update
    float runningTime{0.0f}; // time accumulator

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Calculate elapsed time since last frame
        const float dT{GetFrameTime()};
        runningTime += dT;

        // Update animation frame
        if (runningTime >= updateTime) {
            runningTime = 0.0f;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5) {
                frame = 0;
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        // draw main window
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ground check - stop falling when we hit the ground
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // scarfy is on the ground
            scarfyPos.y = windowHeight - scarfyRec.height;
            velocity = 0;
            isInAir = false;
        }
        else 
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }

        // Update
        //----------------------------------------------------------------------------------
        scarfyPos.y += velocity * dT; // update position with new velocity
        //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scarfy);    // Unload scarfy texture
    UnloadTexture(nebula);    // Unload nebula texture
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}