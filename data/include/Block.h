#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <iostream>
#include <stdio.h>

#include "Entity.h"
#include "TextureManager.h"

struct Block : public Entity
{   
    Block (TextureManager *texturemanager, std::string EntityID, float X, float Y) : Entity(texturemanager, EntityID, X, Y) {
        //yes
    }
};

Block* CreateBlock(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Block* block = new Block(texturemanager, EntityID, X, Y);
    return block;
}

#endif