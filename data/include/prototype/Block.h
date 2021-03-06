#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <iostream>
#include <stdio.h>

#include "Direction.h"
#include "ItemEntity.h"
#include "Entity.h"
#include "../Texture/TextureManager.h"

struct Block : public Entity
{   
    Direction direction;

    std::string prototype;

    Block (TextureManager *texturemanager, std::string EntityID, float X, float Y) : Entity(texturemanager, EntityID, X, Y) {
        //yes
    }

    virtual void Update() { }
    void Update(std::vector<ItemEntity*> items) { }
};

Block* CreateBlock(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Block* block = new Block(texturemanager, EntityID, X, Y);
    return block;
}

#endif