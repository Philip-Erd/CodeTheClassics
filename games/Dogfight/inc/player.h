
#pragma once

#include "raylib.h"
#include "environment.h"
#include "raymath.h"
#include "util.h"
#include <iostream>

#define PITCH_SPEED 0.05
#define ROLL_SPEED 0.5
#define YAW_SPEED 0.05
#define AIR_SPEED 20

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
        int normalMatrixLocation;

        void update(float deltaTime); //update the player
        void draw();                  //draw the player mesh NOT render the player camera
        void drawGizmo();             //draw additional stuff

        void setCamera(Camera &camera); //transforms the raylib camera to the right position+rotation

        float airspeed = 0.025f;

    private:
        Vector3 getUpVector3(); //returns a vector that points up
        float pitch;
        float yaw;
        float roll;

        float down;
        Matrix normalMatrix; //Normal matrix used for lighting
    };
} // namespace Dogfight
