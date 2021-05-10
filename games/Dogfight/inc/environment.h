

#pragma once

#include "raylib.h"
#include "raymath.h"

#define HEIGHT_MAP_SIZE 512

namespace Dogfight
{
    class Environment{
        public:
            Model model;
            Vector3 scale;
            float heights[HEIGHT_MAP_SIZE][HEIGHT_MAP_SIZE];
            

            void draw();
            void generate(Image heightmap, Vector3 scale);
            bool inMap(Vector3 position, float minDistance);
        private:
            
            
            Matrix transform3D;


    };
} // namespace Dogfight

