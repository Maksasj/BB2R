#ifndef TILE_CLASS_H
#define TILE_CLASS_H

#include <iostream>
#include <stdio.h>

#include "Entity.h"
#include "TextureManager.h"

struct Tile : public Entity
{   
    Tile(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Entity(texturemanager, EntityID, X, Y) {
    }
};

Tile* CreateTile(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Tile* tile = new Tile(texturemanager, EntityID, X, Y);
    return tile;
}

#endif