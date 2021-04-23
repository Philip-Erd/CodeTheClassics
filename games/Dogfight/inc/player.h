
#pragma once

#include "raylib.h"
#include "environment.h"
#include "raymath.h"
#include "util.h"
#include <iostream>


#define PITCH_SPEED 5
#define ROLL_SPEED 2
#define YAW_SPEED 5
#define AIR_SPEED 10

namespace Dogfight
{
    class Player
    {
    public:
        int playerNumber;   //number of the player (0 = player 1, 1 = player 2)
        Matrix transform3D; //base matrix
        Vector3 position;   //global position vector
        Model model;        //the model to render
        bool active = true; //if player can fly or is destroyed

        void update(float deltaTime); //update the player
        void draw();                               //draw the player mesh NOT render the player camera
        void drawGizmo();                          //draw additional stuff

        void setCamera(Camera &camera); //transforms the raylib camera to the right position+rotation

    private:
        Vector3 getUpVector3();         //returns a vector that points up
        
        
    
    };
} // namespace Dogfight

