
#include "util.h"

namespace Dogfight
{

    void setupCamera(Camera &camera)
    {
        camera.position = (Vector3){0.0f, 10.0f, 10.0f};
        camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        camera.fovy = 45.0f;
    }

}