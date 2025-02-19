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
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    const int gravity{1'000}; // acceleration due to gravity (pixels/s)/s

    // scarfy variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - neb2Rec.height};

    // nebula animations variables
    int nebFrame;
    const float nebUpdateTime{1.0f / 12.0f};
    float nebRunningTime{0.0f};

    int neb2Frame{};
    const float neb2UpdateTime{1.0f / 16.0f};
    float neb2RunningTime{0.0f};

    int nebVel{-200}; // velocity of the nebula (pizels/s)

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

        // Update scarfy animation frame
        if (!isInAir && runningTime >= updateTime) {
            runningTime = 0.0f;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5) {
                frame = 0;
            }
        }

        // update nebula animation frame
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime) {
            nebRunningTime = 0.0f;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7) {
                nebFrame = 0;
            }
        }
        // update second nebula animation frame
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime) {
            neb2RunningTime = 0.0f;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7) {
                neb2Frame = 0;
            }
        }

        // draw nebula position
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
         //draw second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        // Draw scarfy position 
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
        nebPos.x += nebVel * dT; // update nebula position with new velocity
        neb2Pos.x += nebVel * dT; // update second nebula position with new velocity
        scarfyPos.y += velocity * dT; // update scarfy position with new velocity
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