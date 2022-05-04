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

typedef std::string str;

struct CraftingMachine : public BlockWithStorage
{   
    Recipe Recipe;
    int Speed;

    CraftingMachine(TextureManager *texturemanager, std::string EntityID, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
    }

    void Update() {
        //There we need some rewriting
        if(timer.step % Speed == 0) {
            bool can_craft = true;


            for(auto ingredient : Recipe.ingredients) {
                str id = ingredient.item.id;
                int count = ingredient.count;
                //std::cout << "Checking for: "+id+" "+std::to_string(count)+"\n";

                //Find item in input slots
                bool found = false;
                for(auto input_item : input.cells) {
                    if(input_item.item_id == id) {
                        found = true;
                        if(input_item.count < count) {
                            can_craft = false;
                        }
                    }
                }
                
                if(!found) {
                    can_craft = false;
                    break;
                }
                
            }

            if(can_craft) {
                str product_id = Recipe.result.id;
               //std::cout << "Crafting"+product_id+"\n";
                Result result = put_item(Output, product_id, 1);

                switch (result)
                {
                case SUCCESS:
                    //std::cout << "Successully crafted item and puted in inventory: "+product_id+"\n";
                    
                    break;
                case FULL:
                    //std::cout << "Slot full \n";
                    
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