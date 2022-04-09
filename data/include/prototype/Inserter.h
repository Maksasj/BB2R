#ifndef INSERTER_CLASS_H
#define INSERTER_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Timer.h"
#include "../World/World.h"
#include "BlockWithStorage.h"
#include "../Texture/TextureManager.h"

struct Inserter : public BlockWithStorage
{    
    World *world;

    Inserter(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
        locked = false;
        direction = _place_direction;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() { // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT
        if (direction == 1) { // UP
            if(world->checkBlock(x, y - 64)) {
                Block *tmp_block_first = world->getBlock(x, y - 64);
                if (tmp_block_first->prototype == "BlockWithStorage") {
                    BlockWithStorage* block_with_storage_first_tmp = static_cast<BlockWithStorage*>(world->getBlock(x, y - 64));

                    if (block_with_storage_first_tmp->locked) {
                        
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x, y + 64)) {
                            Block *tmp_block_second = world->getBlock(x, y + 64);
                            if (tmp_block_second->prototype == "BlockWithStorage") {
                                BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x, y + 64));

                                if (!block_with_storage_second_tmp->locked) {
                                    block_with_storage_first_tmp->locked = false;
                                    block_with_storage_second_tmp->locked = true;
                                    block_with_storage_second_tmp->item_holding = block_with_storage_first_tmp->item_holding;
                                }
                            }
                        }
                    }
                }
            }
        } else if (direction == 2) { // DOWN
            if(world->checkBlock(x, y + 64)) {
                Block *tmp_block_first = world->getBlock(x, y + 64);
                if (tmp_block_first->prototype == "BlockWithStorage") {
                    BlockWithStorage* block_with_storage_first_tmp = static_cast<BlockWithStorage*>(world->getBlock(x, y + 64));
                    
                    if (block_with_storage_first_tmp->locked) {
                        
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x, y - 64)) {
                            Block *tmp_block_second = world->getBlock(x, y - 64);
                            if (tmp_block_second->prototype == "BlockWithStorage") {
                                BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x, y - 64));
                                if (!block_with_storage_second_tmp->locked) {
                                    block_with_storage_first_tmp->locked = false;
                                    block_with_storage_second_tmp->locked = true;
                                    block_with_storage_second_tmp->item_holding = block_with_storage_first_tmp->item_holding;
                                }
                            }
                        }
                    }
                }
            }
        } else if (direction == 3) { //LEFT
            if(world->checkBlock(x - 64, y)) {
                Block *tmp_block_first = world->getBlock(x - 64, y);
                if (tmp_block_first->prototype == "BlockWithStorage") {
                    BlockWithStorage* block_with_storage_first_tmp = static_cast<BlockWithStorage*>(world->getBlock(x - 64, y));
                    
                    if (block_with_storage_first_tmp->locked) {
                        
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x + 64, y)) {
                            Block *tmp_block_second = world->getBlock(x + 64, y);
                            if (tmp_block_second->prototype == "BlockWithStorage") {
                                BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x + 64, y));
                                if (!block_with_storage_second_tmp->locked) {
                                    block_with_storage_first_tmp->locked = false;
                                    block_with_storage_second_tmp->locked = true;
                                    block_with_storage_second_tmp->item_holding = block_with_storage_first_tmp->item_holding;
                                }
                            }
                        }
                    }
                }
            }
        } else if (direction == 4) { //RIGHT
            if(world->checkBlock(x + 64, y)) {
                Block *tmp_block_first = world->getBlock(x + 64, y);
                if (tmp_block_first->prototype == "BlockWithStorage") {
                    BlockWithStorage* block_with_storage_first_tmp = static_cast<BlockWithStorage*>(world->getBlock(x + 64, y));
                    
                    if (block_with_storage_first_tmp->locked) {
                        
                        //Checking block what where it wanna put item
                        if(world->checkBlock(x - 64, y)) {
                            Block *tmp_block_second = world->getBlock(x - 64, y);
                            if (tmp_block_second->prototype == "BlockWithStorage") {
                                BlockWithStorage* block_with_storage_second_tmp = static_cast<BlockWithStorage*>(world->getBlock(x - 64, y));
                                if (!block_with_storage_second_tmp->locked) {
                                    block_with_storage_first_tmp->locked = false;
                                    block_with_storage_second_tmp->locked = true;
                                    block_with_storage_second_tmp->item_holding = block_with_storage_first_tmp->item_holding;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);
    }
};

Inserter* CreateInserter(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) {
    Inserter* inserter = new Inserter(texturemanager, EntityID, _place_direction, X, Y);
    return inserter;
}

#endif