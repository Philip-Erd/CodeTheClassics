
#include "environment.h"


namespace Dogfight
{
    
    void Environment::draw(){
        DrawGrid(100, 10);
        DrawModel(model, {0, 0, 0}, 1, WHITE);
    }

    void Environment::generate(Image heightmap, Vector3 scale){
        //generate mesh from texture
        Mesh mesh = GenMeshHeightmap(heightmap, scale);
        model = LoadModelFromMesh(mesh);
        //texture + shader
        model.materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(heightmap);
        model.materials[0].maps[MAP_DIFFUSE].color = GREEN;

    }
} // namespace Dogfight
