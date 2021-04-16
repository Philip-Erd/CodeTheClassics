
#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

class Player{
    public:
        int playerNumber;           //number of the player (0 = player 1, 1 = player 2)
        Matrix transform3D;         //base matrix
        Model model;                //the model to render

        void update(float deltaTime);           //update the player
        void draw();                            //draw the player mesh NOT render the player camera
        void drawGizmo();                       //draw additional stuff

        void setCamera(Camera &camera);         //transforms the raylib camera to the right position+rotation



};

#endif