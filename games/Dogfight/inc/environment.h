

#pragma once

#include "raylib.h"

namespace Dogfight
{
    class Environment{
        public:
            Model model;

            void draw();
            void generate(Image heightmap, Vector3 scale);


    };
} // namespace Dogfight

