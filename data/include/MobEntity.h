#ifndef MOBENTITY_CLASS_H
#define MOBENTITY_CLASS_H

#include <string>

#include "Entity.h"
#include "TextureManager.h"

struct MobEntity : public Entity
{   
    MobEntity(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Entity(texturemanager, EntityID, X, Y) {
    }
};

MobEntity* CreateMobEntity(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    MobEntity* mobentity = new MobEntity(texturemanager, EntityID, X, Y);
    return mobentity;
}

#endif