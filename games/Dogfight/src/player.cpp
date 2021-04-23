
#include "player.h"

namespace Dogfight
{
    void Player::update(float dt)
    {

        Matrix inverse_transform3D = MatrixInvert(transform3D);
        //get input
        float yaw = GetGamepadAxisMovement(playerNumber, 0);
        float pitch = GetGamepadAxisMovement(playerNumber, 1);
        float roll = 0;

        Matrix matrix_pitch = MatrixRotateX(pitch * PITCH_SPEED * dt);
        Vector3 up = getUpVector3();
        Matrix matrix_yaw = MatrixRotate(up, yaw * YAW_SPEED * dt);
        //matrix_yaw = MatrixMultiply(matrix_yaw, MatrixTranslate(position.x, position.y, position.z));

        Matrix matrix_translation = MatrixTranslate(0, 0, AIR_SPEED * dt);
        //matrix_translation = MatrixMultiply(matrix_rotation, matrix_translation);

        transform3D = MatrixMultiply(matrix_pitch, transform3D);
        transform3D = MatrixMultiply(matrix_yaw, transform3D);
        transform3D = MatrixMultiply(matrix_translation, transform3D);

        position = Vector3Transform((Vector3){0, 0, 0}, transform3D);
    }

    void Player::draw()
    {
        model.transform = transform3D;
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
        return up;
    }
} // namespace Dogfight
