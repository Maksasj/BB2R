#ifndef CONTAINER_CLASS_H
#define CONTAINER_CLASS_H

#include <iostream>
#include <raylib.h>
#include <string>

#include "BlockWithStorage.h"

#include "../Renderer/Shader.h"
#include "../Texture/TextureManager.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Timer.h"

struct Container : public BlockWithStorage
{   
    Container(TextureManager *texturemanager, std::string EntityID, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
        single_item = false;
    }

    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);

        //Debug thing \/
        for(auto item : storage.cells) {
            DrawText((item.item_id+" "+std::to_string(item.count)).c_str(), x - camera.x - 5, y - camera.y, 11, RAYWHITE);   
        }
    }
};

Container* CreateContainer(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    Container* container = new Container(texturemanager, EntityID, X, Y);
    return container;
}

#endif