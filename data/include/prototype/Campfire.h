#ifndef CAMPFIRE_CLASS_H
#define CAMPFIRE_CLASS_H

#include <iostream>
#include <raylib.h>

#include "ParticleGenerator.h"
#include "../Shader.h"
#include "../Timer.h"
#include "../World.h"
#include "../Block.h"
#include "../TextureManager.h"
#include "../LightSystem.h"
#include "../utilities/vector.h"

struct Campfire : public Block
{    
    World *world;
    ParticleGenerator *part_gen;

    Campfire(TextureManager *texturemanager, float X, float Y) : Block(texturemanager, "campfire_block", X, Y) {
        part_gen = new ParticleGenerator({x + 32, y + 32}, 10);
        part_gen->tex = texturemanager->Textures["fire_particle"];
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
        part_gen->Update();
    }
    
    void GetLight(LightSystem *lightsystem) {
        lightsystem->LoadLight({x, y}, {0.2, 0.2, 0.8});
    };

    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);
        part_gen->Render();
    }
};

Campfire* CreateCampfire(TextureManager *texturemanager, float X, float Y) {
    Campfire* campfire = new Campfire(texturemanager, X, Y);
    return campfire;
}

#endif