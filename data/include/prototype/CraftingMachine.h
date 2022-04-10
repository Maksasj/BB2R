#ifndef CRAFTINGMACHINE_CLASS_H
#define CRAFTINGMACHINE_CLASS_H

#include <iostream>
#include <raylib.h>

#include "Block.h"
#include "Recipe.h"

#include "../Renderer/Shader.h"
#include "../Texture/TextureManager.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Timer.h"

struct CraftingMachine : public Block
{    
    bool locked;
    std::string item_holding;

    Recipe Recipe;
    int Speed;

    CraftingMachine(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        item_holding = "nothing";
    }

    void Update() {
        if(!locked && timer.step % Speed == 0) {
            bool can_craft = true;
            for(auto ingredient : Recipe.ingredients) {
                //yea
            }

            if(can_craft) {
                item_holding = Recipe.result.id;
                locked = true;
            }

        }
    }
};

CraftingMachine* CreateCraftingMachine(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    CraftingMachine* craftingmachine = new CraftingMachine(texturemanager, EntityID, X, Y);
    return craftingmachine;
}

#endif