
#include "util.h"

namespace Dogfight
{

#pragma region Timer

    //Timer
    void Timer::setTime(double milliseconds)
    {
        waitTime = milliseconds;
    }

    void Timer::start()
    {
        startTime = GetTime();
    }

    bool Timer::hasStopt()
    {

        double elapsedTime = GetTime() - startTime;
        if (elapsedTime > waitTime)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

#pragma endregion Timer

    void setupCamera(Camera &camera)
    {
        camera.position = (Vector3){0.0f, 10.0f, 10.0f};
        camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        camera.fovy = 50.0f;
    }

    float damp(float input, float target, float value){
        float res = Lerp(input, target, value);
        res = Clamp(res, -1, 1);
        
        return res;

    }



}