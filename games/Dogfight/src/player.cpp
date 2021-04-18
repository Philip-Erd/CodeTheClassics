
#include "player.h"

namespace Dogfight
{
    void Player::update(float dt){

    }

    void Player::draw(){
        model.transform = transform3D;
        DrawModel(model, Vector3Zero(), 1, WHITE);
    }

    void Player::drawGizmo(){

    }

    void Player::setCamera(Camera &camera){
        camera.position = Vector3Transform((Vector3){0, 8, -24}, transform3D);
        camera.target = Vector3Transform((Vector3){0, 0, 100}, transform3D);
    }
} // namespace Dogfight
