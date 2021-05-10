
#pragma once

#include "raylib.h"
#include "environment.h"
#include "raymath.h"
#include "util.h"
#include "bullet.h"

#define PITCH_SPEED 0.05
#define ROLL_SPEED 0.5
#define YAW_SPEED 0.05
#define AIR_SPEED 20
#define BULLET_SPEED 250

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

        int health;
        Bullet bullets[100];        //the bullets the player shoots



        void update(float deltaTime); //update the player
        void draw();                  //draw the player mesh NOT render the player camera
        void drawGizmo();             //draw additional stuff

        void damage(int damage);        //take the given amount of damage
        void reset();                   //resets the player after he died

        void setCamera(Camera &camera); //transforms the raylib camera to the right position+rotation

    private:
        Vector3 getUpVector3(); //returns a vector that points up
        float pitch;
        float yaw;
        float roll;
        float airspeed = 0.025f;
        float down;
        Matrix normalMatrix; //Normal matrix used for lighting
        int bulletIndex = 0;    //used to determin where to put the new bullet 
    };
} // namespace Dogfight
