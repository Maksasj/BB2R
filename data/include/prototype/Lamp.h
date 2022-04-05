#ifndef LAMP_CLASS_H
#define LAMP_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Shader.h"
#include "../Timer.h"
#include "../World.h"
#include "../Block.h"
#include "../TextureManager.h"
#include "../LightSystem.h"
#include "../utilities/vector.h"

struct Lamp : public Block
{    
    World *world;

    Lamp(TextureManager *texturemanager, float X, float Y) : Block(texturemanager, "lamp", X, Y) {
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