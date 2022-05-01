#ifndef ORE_ROCK_CLASS_H
#define ORE_ROCK_CLASS_H

#include <string>

#include "../Texture/TextureManager.h"
#include "Block.h"

struct Ore_Rock : public Block
{    
    int hardness;
    std::string ore_id;

    Ore_Rock(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        
    }

};

Ore_Rock* CreateOre_Rock(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Ore_Rock* ore_rock = new Ore_Rock(texturemanager, EntityID, X, Y);
    return ore_rock;
}

#endif