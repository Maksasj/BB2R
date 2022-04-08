#ifndef ITEMENTITY_CLASS_H
#define ITEMENTITY_CLASS_H

#include <string>

#include "Entity.h"
#include "../Texture/TextureManager.h"

struct ItemEntity : public Entity
{   
    int count;

    ItemEntity(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Entity(texturemanager, EntityID, X, Y) {
        count = 1;
    }
};

ItemEntity* CreateItemEntity(TextureManager *texturemanager, std::string EntityID, int _count, float X, float Y) {
    ItemEntity* itementity = new ItemEntity(texturemanager, EntityID, X, Y);
    itementity->count = _count;
    return itementity;
}

#endif