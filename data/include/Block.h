#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <iostream>
#include <stdio.h>

#include "ItemEntity.h"
#include "Entity.h"
#include "TextureManager.h"

struct Block : public Entity
{   
    bool locked;
    int direction; // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT

    Block (TextureManager *texturemanager, std::string EntityID, float X, float Y) : Entity(texturemanager, EntityID, X, Y) {
        //yes
    }

    void Update() { }
    virtual void PickUpItem(ItemEntity* item) {};
    virtual int Get(std::string id) {};
    void Update(std::vector<ItemEntity*> items) { }
};

Block* CreateBlock(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Block* block = new Block(texturemanager, EntityID, X, Y);
    return block;
}

#endif