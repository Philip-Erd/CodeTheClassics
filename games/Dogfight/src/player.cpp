
#include "player.h"

namespace Dogfight
{
    void Player::update(float dt)
    {

        //get input
        float i_yaw = -GetGamepadAxisMovement(playerNumber, 0);
        float i_pitch = GetGamepadAxisMovement(playerNumber, 1);
        yaw = damp(yaw, i_yaw, 2 * dt);
        pitch = damp(pitch, i_pitch, 2 * dt);
        roll = yaw;

        //Calculating how much the nose is pointing down
        down = Vector3Distance(Vector3Add({0, 1, 0}, position), Vector3Transform({0, 0, 1}, transform3D));
        airspeed = Lerp(airspeed, down * dt * 3, 0.002f);
        airspeed = Clamp(airspeed, 0.01, 0.1);

        Matrix matrix_pitch = MatrixRotateX(pitch * PITCH_SPEED);
        Matrix matrix_yaw = MatrixRotate(getUpVector3(), yaw * YAW_SPEED);

        Matrix matrix_translation = MatrixTranslate(0, 0, airspeed * AIR_SPEED);

        transform3D = MatrixMultiply(matrix_pitch, transform3D);
        transform3D = MatrixMultiply(matrix_yaw, transform3D);
        transform3D = MatrixMultiply(matrix_translation, transform3D);

        position = Vector3Transform((Vector3){0, 0, 0}, transform3D);

        //Collision is done in game.cpp

        //shoot
        bool shoot = false;
        shoot = IsGamepadButtonDown(playerNumber, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
        if(shoot){
            bullets[bulletIndex].position = position;
            Vector3 vel = Vector3Transform({0, 0, 1}, normalMatrix);
            bullets[bulletIndex].velocity = vel;
            bullets[bulletIndex].active = true;
            bulletIndex = (bulletIndex + 1)%100;
        }

        //update bullets
        for(int i = 0; i < 100; i++){
            if(bullets[i].active){
                bullets[i].position = Vector3Add(bullets[i].position, Vector3Scale(bullets[i].velocity, dt * BULLET_SPEED));
            }
        }

        //rendering updates
        //some fancy roll animation
        Matrix model_transform3D = transform3D;
        Matrix rotation = MatrixRotateZ(yaw * ROLL_SPEED);
        model.transform = MatrixMultiply(rotation, model_transform3D);

        normalMatrix = MatrixInvert(model_transform3D);
        normalMatrix = MatrixTranspose(normalMatrix);

    }

    void Player::draw()
    {

        SetShaderValueMatrix(model.materials[0].shader, normalMatrixLocation, normalMatrix);

        DrawModel(model, Vector3Zero(), 1, WHITE);
    }

    void Player::drawGizmo()
    {
        Vector3 origin = Vector3Transform((Vector3){0, 0, 0}, transform3D);
        Vector3 x = Vector3Transform((Vector3){10, 0, 0}, transform3D);
        Vector3 y = Vector3Transform((Vector3){0, 10, 0}, transform3D);
        Vector3 z = Vector3Transform((Vector3){0, 0, 10}, transform3D);


        DrawLine3D(origin, x, RED);
        DrawLine3D(origin, y, GREEN);
        DrawLine3D(origin, z, BLUE);
    }

    void Player::setCamera(Camera &camera)
    {
        camera.position = Vector3Transform((Vector3){0, 8, -24}, transform3D);
        camera.target = Vector3Transform((Vector3){0, 0, 100}, transform3D);
        //camera.up = Vector3Transform((Vector3){0, 8, -24}, transform3D);
        camera.up = (Vector3){0, 1, 0};
    }

    Vector3 Player::getUpVector3(){
        //took me way to long to figure this out
        Vector3 up = {0, 1, 0};
        up = Vector3Add(up, position);
        up = Vector3Transform(up, MatrixInvert(transform3D));
        up = Vector3Normalize(up);
        return up;
    }
} // namespace Dogfight
