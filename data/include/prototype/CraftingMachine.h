#ifndef CRAFTINGMACHINE_CLASS_H
#define CRAFTINGMACHINE_CLASS_H

#include <iostream>
#include <raylib.h>

#include "BlockWithStorage.h"
#include "Recipe.h"

#include "../Renderer/Shader.h"
#include "../Texture/TextureManager.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Timer.h"

struct CraftingMachine : public BlockWithStorage
{   
    Recipe Recipe;
    int Speed;

    CraftingMachine(TextureManager *texturemanager, std::string EntityID, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
        locked = false;
    }

    void Update() {
        if(!locked && timer.step % Speed == 0) {
            bool can_craft = true;
            for(auto ingredient : Recipe.ingredients) {
                //yea
            }

            if(can_craft) {
                std::string product_id = Recipe.result.id;
                std::cout << "Crafted item: "+ product_id << "\n";

                RESULT result = put_item(Output, product_id, 1);

                switch (result)
                {
                case SUCCESS:
                    std::cout << "Successully putted item in needed slot \n";
                    
                    break;
                case FULL:
                    std::cout << "Slot full \n";


                    break;
            
                default:
                    break;
                }
            }

        }
    }
};

CraftingMachine* CreateCraftingMachine(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    CraftingMachine* craftingmachine = new CraftingMachine(texturemanager, EntityID, X, Y);
    return craftingmachine;
}

#endif