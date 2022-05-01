#ifndef CROP_CLASS_H
#define CROP_CLASS_H

#include <string>

#include "../Texture/TextureManager.h"
#include "Block.h"

struct Crop : public Block
{
    int stage;
    int max_stage;

    int speed;

    Crop(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        max_stage = 5;
        speed = 120;
        stage = 0;
    }

    void Update() {
        if (timer.step % speed == 0 && stage != max_stage)
            stage++;

        if (stage >= max_stage)
            stage = 0;
    }

    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);
        DrawText(std::to_string(stage).c_str(), x - camera.x, y - camera.y, 11, RAYWHITE);   
    }
};

Crop* CreateCrop(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Crop* crop = new Crop(texturemanager, EntityID, X, Y);
    return crop;
}

#endif