#ifndef LAMP_CLASS_H
#define LAMP_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Renderer/Shader.h"
#include "../Timer.h"
#include "../World/World.h"
#include "Block.h"
#include "../Texture/TextureManager.h"
#include "../Renderer/LightSystem.h"
#include "../Utilities/vector.h"

struct Lamp : public Block
{    
    World *world;

    Lamp(TextureManager *texturemanager, float X, float Y) : Block(texturemanager, "lamp_block", X, Y) {
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
    }
    
    void GetLight(LightSystem *lightsystem) {
        lightsystem->LoadLight({x, y}, {0.2, 0.2, 0.8});
    };

    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);
    }
};

Lamp* CreateLamp(TextureManager *texturemanager, float X, float Y) {
    Lamp* lamp = new Lamp(texturemanager, X, Y);
    return lamp;
}

#endif