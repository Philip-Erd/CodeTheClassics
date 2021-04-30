
#include "game.h"


#include <emscripten/emscripten.h>


int screenWidth = 1200;
int screenHeight = 675;



void UpdateDrawFrame(void);     


int main()
{


    InitWindow(screenWidth, screenHeight, "Dogfight");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Dogfight::initGame();

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

}

void UpdateDrawFrame(void)
{

    Dogfight::updateGame(GetFrameTime());

    Dogfight::drawGame();

}