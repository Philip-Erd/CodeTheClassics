#pragma once


#include "environment.h"
#include "raylib.h"
#include "util.h"
#include "player.h"

#include "raymath.h"
//#include "rlights.h"


namespace Dogfight
{
    void initGame();                    //init function called at game startup
    void updateGame(float deltaTime);   //general update function
    void drawGame();                    //general draw function
}
