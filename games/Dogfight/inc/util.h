
#pragma once

#include "raylib.h"
#include "raymath.h"

namespace Dogfight
{


    //timer
    class Timer{
        public:
            void setTime(double milliseconds);
            void start();
            bool hasStopt();
        private:
            double waitTime;
            double startTime;
    };



    //Basic camera setup
    void setupCamera(Camera &camera);
    float damp(float input, float target, float value);      //interpolates the input towards the target by the given strngth


} // namespace Dogfight
