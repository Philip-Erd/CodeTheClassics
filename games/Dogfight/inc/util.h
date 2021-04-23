
#pragma once

#include "raylib.h"

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


} // namespace Dogfight
