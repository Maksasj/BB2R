#ifndef DRILL_CLASS_H
#define DRILL_CLASS_H

#include <iostream>
#include <raylib.h>

#include "Block.h"
#include "Ore_Rock.h"

#include "../Renderer/Shader.h"
#include "../Texture/TextureManager.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Timer.h"

struct Drill : public Block
{   
    World *world;
    int Speed;
    int hardness;

    Drill(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        direction = _place_direction;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
        if(timer.step % Speed == 0) {
            if (direction == 1) { // UP
                if(world->checkBlock(x, y - 64)) {
                    //This part can be unsafe
                    Ore_Rock* ore_block = static_cast<Ore_Rock*>(world->getBlock(x, y - 64));

                    if (ore_block->prototype == "Ore_Rock" && hardness >= ore_block->hardness) {
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x, y + 64)) {
                            //Also this part can be very unsafe
                            BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x, y + 64));

                            if (!block_with_storage_second_tmp->locked) {
                                block_with_storage_second_tmp->locked = true;
                                block_with_storage_second_tmp->item_holding = ore_block->ore_id;
                            }
                        }
                    }
                }
            } else if (direction == 2) { // DOWN
                if(world->checkBlock(x, y + 64)) {
                    //This part can be unsafe
                    Ore_Rock* ore_block = static_cast<Ore_Rock*>(world->getBlock(x, y + 64));

                    if (ore_block->prototype == "Ore_Rock" && hardness >= ore_block->hardness) {
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x, y - 64)) {
                            //Also this part can be very unsafe
                            BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x, y - 64));

                            if (!block_with_storage_second_tmp->locked) {
                                block_with_storage_second_tmp->locked = true;
                                block_with_storage_second_tmp->item_holding = ore_block->ore_id;
                            }
                        }
                    }
                }
            } else if (direction == 3) { //LEFT
                if(world->checkBlock(x - 64, y)) {
                    //This part can be unsafe
                    Ore_Rock* ore_block = static_cast<Ore_Rock*>(world->getBlock(x - 64, y));

                    if (ore_block->prototype == "Ore_Rock" && hardness >= ore_block->hardness) {
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x + 64, y)) {
                            //Also this part can be very unsafe
                            BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x + 64, y));

                            if (!block_with_storage_second_tmp->locked) {
                                block_with_storage_second_tmp->locked = true;
                                block_with_storage_second_tmp->item_holding = ore_block->ore_id;
                            }
                        }
                    }
                }
            } else if (direction == 4) { //RIGHT
                if(world->checkBlock(x + 64, y)) {
                    //This part can be unsafe
                    Ore_Rock* ore_block = static_cast<Ore_Rock*>(world->getBlock(x + 64, y));

                    if (ore_block->prototype == "Ore_Rock" && hardness >= ore_block->hardness) {
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x - 64, y)) {
                            //Also this part can be very unsafe
                            BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x - 64, y));

                            if (!block_with_storage_second_tmp->locked) {
                                block_with_storage_second_tmp->locked = true;
                                block_with_storage_second_tmp->item_holding = ore_block->ore_id;
                            }
                        }
                    }
                }
            }
        }
    }
};

Drill* CreateDrill(TextureManager *texturemanager, std::string EntityID, int _place_direction,float X, float Y) {
    Drill* drill = new Drill(texturemanager, EntityID, _place_direction, X, Y);
    return drill;
}

#endif