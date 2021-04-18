
#include "game.h"
#include "stdio.h"

namespace Dogfight
{

    //game
    Player player1;
    Player player2;

    Environment environment;


    //rendering
    Camera cameraP1 = {0};
    Camera cameraP2 = {0};

    RenderTexture renderTargetP1;
    RenderTexture renderTargetP2;

    Rectangle viewportP1;
    Rectangle viewportP2;

    Shader simpleShader;

    bool player1Available = true;
    bool player2Available = true;


    void initGame()
    {

        //shader
        simpleShader = LoadShader("res/simple.vs", "res/simple.fs");

#pragma region Player
        //load player models
        player1.model = LoadModel("res/Plane1.gltf");
        player2.model = LoadModel("res/Plane1.gltf");

        player1.model.materials[0].shader = simpleShader;
        player2.model.materials[0].shader = simpleShader;

        //initialize transforms
        player1.transform3D = MatrixTranslate(0, 0, 0);
        player2.transform3D = MatrixTranslate(20, 0, 0);



#pragma endregion



#pragma region Rendering
        //rendering

        //setup cameras
        setupCamera(cameraP1);
        setupCamera(cameraP2);

        //setup rendertargets
        renderTargetP1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() / 2);
        renderTargetP2 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() / 2);

        //setup viewports
        viewportP1 = {0, 0, (float)renderTargetP1.texture.width, (float)-renderTargetP1.texture.height};
        viewportP2 = {0, 0, (float)renderTargetP2.texture.width, (float)-renderTargetP2.texture.height};

#pragma endregion
    }

    void updateGame(float dt)
    {
        //update players

        //update cameras
        player1.setCamera(cameraP1);
        player2.setCamera(cameraP2);
    }

    void drawGame()
    {

        //draw p1
        BeginTextureMode(renderTargetP1);

        if (player1Available)
        {
            BeginMode3D(cameraP1);
            ClearBackground(RAYWHITE);

            player1.draw();
            player2.draw();
            environment.draw();

            EndMode3D();
        }
        else
        {
            ClearBackground(BLUE);
            DrawText("Player 1 is not available", 10, 10, 30, BLACK);
        }

        EndTextureMode();

        //draw p2
        BeginTextureMode(renderTargetP2);

        if (player2Available)
        {
            BeginMode3D(cameraP2);

            player1.draw();
            player2.draw();
            environment.draw();

            EndMode3D();
        }
        else
        {
            ClearBackground(RED);
            DrawText("Player 2 is not available", 10, 10, 30, BLACK);
            //DrawRectangle(0, 0, 1000, 1000, BLACK);
        }

        EndTextureMode();

        //draw main
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureRec(renderTargetP1.texture, viewportP1, (Vector2){0, 0}, WHITE);
        DrawTextureRec(renderTargetP2.texture, viewportP2, (Vector2){0, (float)GetScreenHeight() / 2}, WHITE);
        //DrawTextureRec(renderTargetP2.texture, viewportP2, (Vector2){0, 0}, WHITE);

        EndDrawing();
    }

}