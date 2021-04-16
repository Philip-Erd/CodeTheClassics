
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "raymath.h"
#include "util.h"

namespace Dogfight
{
    void initGame();                    //init function called at game startup
    void updateGame(float deltaTime);   //general update function
    void drawGame();                    //general draw function
}

#endif