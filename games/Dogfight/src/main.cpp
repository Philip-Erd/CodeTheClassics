
#include "game.h"


#include <emscripten/emscripten.h>


int screenWidth = 800;
int screenHeight = 450;



void UpdateDrawFrame(void);     


int main()
{


    InitWindow(screenWidth, screenHeight, "Dogfight");
    SetTargetFPS(60);

    Dogfight::initGame();

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

}

void UpdateDrawFrame(void)
{

    Dogfight::updateGame(GetFrameTime());

    Dogfight::drawGame();

}