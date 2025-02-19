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
  
    AnimData nebulae[3] = {};

    for (int i = 0; i < 3; i++) {
        nebulae[i].rec.x = 0.0f;
        nebulae[i].rec.y = 0.0f;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;

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
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime) {
            nebulae[0].runningTime = 0.0f;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7) {
                nebulae[0].frame = 0;
            }
        }

        // Update second nebula animation frame
        nebulae[1].runningTime += dT;
        if (nebulae[1].runningTime >= nebulae[1].updateTime) {
            nebulae[1].runningTime = 0.0f;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7) {
                nebulae[1].frame = 0;
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

        // Update nebulae positions
        nebulae[0].pos.y += nebVel * dT;
        nebulae[1].pos.x += nebVel * dT;
        
        // Update scarfy's position
        scarfyData.pos.y += velocity * dT;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw nebulae
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, WHITE);

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