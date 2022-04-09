#ifndef BLOCKWITHSTORAGE_CLASS_H
#define BLOCKWITHSTORAGE_CLASS_H

#include <iostream>
#include <raylib.h>

#include "ParticleGenerator.h"
#include "../Renderer/Shader.h"
#include "../Timer.h"
#include "../World/World.h"
#include "Block.h"
#include "../Texture/TextureManager.h"
#include "../Renderer/LightSystem.h"
#include "../Utilities/vector.h"

struct BlockWithStorage : public Block
{    
    bool locked;
    std::string item_holding;

    BlockWithStorage(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        item_holding = "red_fish";
        prototype = "BlockWithStorage";
        locked = false;
    }
};

#endif