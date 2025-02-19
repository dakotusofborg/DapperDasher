#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int windowDimensions[2] = {512, 380};

    // Initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000}; // acceleration due to gravity (pixels/s)/s

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // AnimData for nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0.0, 0.0, static_cast<float>(nebula.width) / 8, static_cast<float>(nebula.height) / 8}, // Rectangle rec
        {static_cast<float>(windowDimensions[0]), static_cast<float>(windowDimensions[1]) - static_cast<float>(nebula.height) / 8}, // Vector2 pos
        0, // int frame
        1.0 / 12.0, // float updateTime
        0.0 // float runningTime
    };

    // AnimData for second nebula
    AnimData neb2Data{
        {0.0, 0.0, static_cast<float>(nebula.width) / 8, static_cast<float>(nebula.height) / 8}, // Rectangle rec
        {static_cast<float>(windowDimensions[0] + 300), static_cast<float>(windowDimensions[1]) - static_cast<float>(nebula.height) / 8}, // Vector2 pos
        0, // int frame
        1.0 / 16.0, // float updateTime
        0.0 // float runningTime
    };

    int nebVel{-200}; // velocity of the nebula (pixels/s)

    // is the rectangle in the air?
    bool isInAir{};   
    // jump velocity
    const int jumpVel{-600}; // pixels/s

    int velocity{0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Calculate elapsed time since last frame
        const float dT{GetFrameTime()};
        scarfyData.runningTime += dT;

        // Update scarfy animation frame
        if (!isInAir && scarfyData.runningTime >= scarfyData.updateTime) {
            scarfyData.runningTime = 0.0f;
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;
            if (scarfyData.frame > 5) {
                scarfyData.frame = 0;
            }
        }

        // Update nebula animation frame
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime) {
            nebData.runningTime = 0.0f;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7) {
                nebData.frame = 0;
            }
        }

        // Update second nebula animation frame
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime) {
            neb2Data.runningTime = 0.0f;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7) {
                neb2Data.frame = 0;
            }
        }

        // Update
        //----------------------------------------------------------------------------------
        // ground check - stop falling when we hit the ground
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) {
            // scarfy is on the ground
            scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
            velocity = 0;
            isInAir = false;
        } else {
            // scarfy is in the air
            velocity += gravity * dT;
            isInAir = true;
        }
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }

        // Update scarfy's position
        scarfyData.pos.y += velocity * dT;

        // Update nebula positions
        nebData.pos.x += nebVel * dT;
        neb2Data.pos.x += nebVel * dT;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw nebulae
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

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