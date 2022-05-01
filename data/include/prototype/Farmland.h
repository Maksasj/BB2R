#ifndef FARMLAND_CLASS_H
#define FARMLAND_CLASS_H

#include <string>

#include "../Texture/TextureManager.h"
#include "Tile.h"

struct Farmland : public Tile
{    
    float grow_multiplier;

    Farmland(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Tile(texturemanager, EntityID, X, Y) {
        
    }

};

Farmland* CreateFarmland(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Farmland* farmland = new Farmland(texturemanager, EntityID, X, Y);
    return farmland;
}

#endif