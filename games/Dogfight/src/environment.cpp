
#include "environment.h"


namespace Dogfight
{
    
    void Environment::draw(){
        DrawGrid(100, 10);
        DrawModel(model, {0, 0, 0}, 1, WHITE);
    }

    void Environment::generate(Image heightmap_p, Vector3 scale_p){

        //unload old model if present
        if(true){
            UnloadModel(model);
        }

        //generate mesh from texture
        Mesh mesh = GenMeshHeightmap(heightmap_p, {1, 1, 1});
        model = LoadModelFromMesh(mesh);
        scale = scale_p;

        //generate heights values
        Color *pixels = LoadImageColors(heightmap_p);

        for(int x = 0; x < HEIGHT_MAP_SIZE; x++){
            for(int y = 0; y < HEIGHT_MAP_SIZE; y++){
                heights[x][y] = pixels[x + (y * HEIGHT_MAP_SIZE)].r;
            }
        }

        UnloadImageColors(pixels);

        //transform
        Matrix matrix_scale = MatrixScale(scale.x, scale.y, scale.z);
        //Matrix translation = MatrixTranslate(-1250, 0, -1250);
        Matrix matrix_translation = MatrixTranslate(0, 0, 0);

        transform3D = MatrixMultiply(matrix_scale, matrix_translation);
        model.transform = transform3D;

        //texture + shader
        model.materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(heightmap_p);

    }

    bool Environment::inMap(Vector3 position, float minDistance){
        bool res = false;

        //get position in 2d map space
        Vector2 pos_2d = {position.x / (scale.x / HEIGHT_MAP_SIZE), position.z / (scale.z / HEIGHT_MAP_SIZE)};

        if(pos_2d.x > HEIGHT_MAP_SIZE || pos_2d.x < 0 || pos_2d.y > HEIGHT_MAP_SIZE || pos_2d.y < 0){
            return false;
        }
        //get height from map
        float height = 10 * heights[(int)pos_2d.x][(int)pos_2d.y];

        if((position.y - height) < minDistance){
            res = true;
        }
        return res;
    }
} // namespace Dogfight
