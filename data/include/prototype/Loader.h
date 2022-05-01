#ifndef LOADER_CLASS_H
#define LOADER_CLASS_H

#include <iostream>
#include <raylib.h>

#include "Block.h"
#include "Ore_Rock.h"

#include "../Renderer/Shader.h"
#include "../Texture/TextureManager.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Timer.h"

struct Loader : public Block
{   
    World *world;
    int Speed;
    int hardness;

    Loader(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        direction = _place_direction;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
        if(timer.step % Speed == 0) {
            //yes
        }
    }
};

Loader* CreateLoader(TextureManager *texturemanager, std::string EntityID, int _place_direction,float X, float Y) {
    Loader* loader = new Loader(texturemanager, EntityID, _place_direction, X, Y);
    return loader;
}

#endif