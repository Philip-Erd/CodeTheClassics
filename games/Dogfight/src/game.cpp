
#include "game.h"
#include "stdio.h"



namespace Dogfight
{

    //general
    float deltaTime;

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

    bool player1Available = true;
    bool player2Available = true;


    void initGame()
    {

        //shader
        Shader planeShader = LoadShader("res/PlaneShader/plane.vs", "res/PlaneShader/plane.fs");
        Shader environmentShader = LoadShader("res/EnvironmentShader/environment.vs", "res/EnvironmentShader/environment.fs");

        //set sun
        float sunDir[] = {-1.0, 0.0, 0.0};
        //SetShaderValue(diffuseShader, GetShaderLocation(diffuseShader, "sunDir"), sunDir, SHADER_UNIFORM_VEC3);
        SetShaderValue(planeShader, GetShaderLocation(planeShader, "sunDir"), sunDir, 2);
        SetShaderValue(environmentShader, GetShaderLocation(environmentShader, "sunDir"), sunDir, 2);
        float sunColor[] = {1.0, 1.0, 1.0};
        //SetShaderValue(diffuseShader, GetShaderLocation(diffuseShader, "sunColor"), sunColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(planeShader, GetShaderLocation(planeShader, "sunColor"), sunColor, 2);
        SetShaderValue(environmentShader, GetShaderLocation(environmentShader, "sunColor"), sunColor, 2);

        

#pragma region Player

        //load player models
        player1.model = LoadModel("res/Plane1.gltf");
        player2.model = LoadModel("res/Plane1.gltf");
        //load textures
        Texture textureP1 = LoadTexture("res/Color_p1.png");
        Texture textureP2 = LoadTexture("res/Color_p2.png");

        player1.model.materials[0].shader = planeShader;
        player1.model.materials[0].maps[MAP_DIFFUSE].texture = textureP1;
        player1.model.materials[0].maps[MAP_DIFFUSE].color = WHITE;

        player2.model.materials[0].shader = planeShader;
        player2.model.materials[0].maps[MAP_DIFFUSE].texture = textureP2;
        player2.model.materials[0].maps[MAP_DIFFUSE].color = WHITE;

        int normalMatrixLocation = GetShaderLocation(planeShader, "matNormal");
        if(normalMatrixLocation == -1){
            std::cout << "couldn get matNormal location";
        }
        player1.normalMatrixLocation = normalMatrixLocation;
        player2.normalMatrixLocation = normalMatrixLocation;

        //initialize transforms
        player1.transform3D = MatrixTranslate(1000, 0, 0);
        player2.transform3D = MatrixTranslate(20, 0, 0);

        //set player number
        player1.playerNumber = 0;
        player2.playerNumber = 1;



#pragma endregion

#pragma region environment
        //set up the environment
        Image heightmap = LoadImage("res/environments/0.png");
        environment.generate(heightmap, {1000, 500, 1000});

        environment.model.materials[0].shader = environmentShader;


        Texture2D texGrass = LoadTexture("res/grass.png");
        Texture2D texStone = LoadTexture("res/stone.png");
        //SetTextureWrap(texGrass, TEXTURE_WRAP_REPEAT);
        //SetTextureWrap(texStone, TEXTURE_WRAP_REPEAT);
        SetTextureWrap(texGrass, 0);
        SetTextureWrap(texStone, 0);

        environment.model.materials[0].maps[1].texture = texGrass;
        environment.model.materials[0].maps[2].texture = texStone;

        
        
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
        //deltaTime
        deltaTime = GetFrameTime();

        //get availability
        if(IsGamepadAvailable(0)){
            player1Available = true;
        }else{
            player1Available = false;
        }

        if(IsGamepadAvailable(1)){
            player2Available = true;
        }else{
            player2Available = false;
        }

        //update players
        if(player1Available){
            player1.update(deltaTime);              //update player
            player1.setCamera(cameraP1);            //update camera

        }

        if(player2Available){
            player2.update(deltaTime);              //update player
            player2.setCamera(cameraP2);            //update camera

        }
 

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

            player1.drawGizmo();

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
            ClearBackground(RAYWHITE);

            player1.draw();
            player2.draw();
            environment.draw();

            player1.drawGizmo();

            EndMode3D();
        }
        else
        {
            ClearBackground(RED);
            DrawText("Player 2 is not available", 10, 10, 30, BLACK);
        }

        EndTextureMode();

        //draw main
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureRec(renderTargetP1.texture, viewportP1, (Vector2){0, 0}, WHITE);
        DrawTextureRec(renderTargetP2.texture, viewportP2, (Vector2){0, (float)GetScreenHeight() / 2}, WHITE);

        //DrawText(TextFormat("Airspeed: %f", player1.airspeed), 10, 10, 32, BLACK);

        EndDrawing();
    }

}