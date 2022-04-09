#ifndef FISHFARM_CLASS_H
#define FISHFARM_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Timer.h"
#include "../World/World.h"
#include "../Texture/TextureManager.h"

#include "BlockWithStorage.h"

struct FishFarm : public BlockWithStorage
{    
    int speed = 16000;

    FishFarm(TextureManager *texturemanager, std::string EntityID, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
        locked = false;
        item_holding = "red_fish";
    }

    void Update() {
        if (locked == false && timer.step % speed == 0) {
            locked = true;
        }
           
    }
    
    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);
    }
};

FishFarm* CreateFishFarm(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    FishFarm* fishfarm = new FishFarm(texturemanager, EntityID, X, Y);
    return fishfarm;
}

#endif