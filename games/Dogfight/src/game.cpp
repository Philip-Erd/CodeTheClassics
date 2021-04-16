
#include "game.h"


//rendering
Camera cameraP1 = {0};
Camera cameraP2 = {0};

RenderTexture2D renderTargetP1;
RenderTexture2D renderTargetP2;

Rectangle viewportP1;
Rectangle viewportP2;

bool player1Available = false;
bool player2Available = false;


namespace Dogfight
{
    void initGame()
    {

        //rendering

        //setup cameras
        setupCamera(cameraP1);
        setupCamera(cameraP2);

        //setup rendertargets
        renderTargetP1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);
        renderTargetP1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);


        //setup viewports
        
        viewportP1 = { 0, 0, (float)renderTargetP1.texture.width, (float)-renderTargetP1.texture.height};
        viewportP2 = { 0, 0, (float)renderTargetP2.texture.width, (float)-renderTargetP2.texture.height};
    }

    void updateGame(float dt)
    {
    }

    void drawGame()
    {

        //draw p1
        BeginTextureMode(renderTargetP1);

        if(player1Available){
            BeginMode3D(cameraP1);

            EndMode3D();
        }else{
            ClearBackground(BLUE);
            DrawText("P1 not available", 10, 10, 30, BLACK);
        }

        EndTextureMode();


        //draw p2
        BeginTextureMode(renderTargetP2);

        if(player2Available){
            BeginMode3D(cameraP2);

            EndMode3D();
        }else{
            ClearBackground(RED);
            DrawText("P2 not available", 10, 10, 50, BLACK);
            DrawLine(0, 0, renderTargetP2.texture.width, renderTargetP2.texture.height, BLACK);
        }

        EndTextureMode();

        //draw main
        BeginDrawing();

        DrawTextureRec(renderTargetP1.texture, viewportP1, (Vector2){0, 0}, WHITE);
        DrawTextureRec(renderTargetP2.texture, viewportP2, (Vector2){0, (float)GetScreenHeight()/2}, WHITE);

        EndDrawing();
    }

}