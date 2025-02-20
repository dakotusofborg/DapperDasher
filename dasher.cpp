#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

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
    scarfyData.updateTime = 1.0 / 6.0;
    scarfyData.runningTime = 0.0;

    // AnimData for nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae] = {};

    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].rec.x = 0.0f;
        nebulae[i].rec.y = 0.0f;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = windowDimensions[0] + i * 300; // Set pos.x based on index
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 12.0;
    }

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
        if (!isInAir) {
            scarfyData = updateAnimData(scarfyData, dT, 5); 
        }

        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        // Update
        //----------------------------------------------------------------------------------
        // ground check - stop falling when we hit the ground
        if (isOnGround(scarfyData, windowDimensions[1])) {
            // scarfy is on the ground
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

        for (int i = 0; i < sizeOfNebulae; i++) {
            // update nebula positions
            nebulae[i].pos.x += nebVel * dT;
        }
        
        // Update scarfy's position
        scarfyData.pos.y += velocity * dT;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < sizeOfNebulae; i++) {
            // draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

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