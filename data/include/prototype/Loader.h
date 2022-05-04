#ifndef LOADER_CLASS_H
#define LOADER_CLASS_H

#include <iostream>
#include <raylib.h>

#include "Block.h"
#include "BlockWithStorage.h"

#include "../Renderer/Shader.h"
#include "../Texture/TextureManager.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Timer.h"

struct Loader : public Block
{   
    World *world;

    Loader(TextureManager *texturemanager, std::string EntityID, Direction _place_direction, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        direction = _place_direction;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
        switch (direction)
        {
        case North:
            if(world->checkBlock(x, y + 64)) { 
                bws block = dynamic_cast<bws>(world->getBlock(x, y + 64));

                if(block != NULL) {
                    GetItemResult getitemresult = block->get_item();
                    if(getitemresult.result != EMPTY && world->checkBlock(x, y - 64)) {
                        bws block1 = dynamic_cast<bws>(world->getBlock(x, y - 64));

                        if(block1 != NULL) {
                            CellType cell_type = block1->cell_priority(PUT);
                            if(cell_type != Null) {
                                Result result = block1->put_item(cell_type, getitemresult.item_id, 1);
                                if(result == SUCCESS) {
                                    //std::cout << "Succesfully putted item, in: " << cell_type;
                                    //block->s_output.count = 0;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case West:
            if(world->checkBlock(x + 64, y)) { 
                bws block = dynamic_cast<bws>(world->getBlock(x + 64, y));

                if(block != NULL) {
                    GetItemResult getitemresult = block->get_item();
                    if(getitemresult.result != EMPTY && world->checkBlock(x - 64, y)) {
                        bws block1 = dynamic_cast<bws>(world->getBlock(x - 64, y));

                        if(block1 != NULL) {
                            CellType cell_type = block1->cell_priority(PUT);
                            if(cell_type != Null) {
                                Result result = block1->put_item(cell_type, getitemresult.item_id, 1);
                                if(result == SUCCESS) {
                                    //std::cout << "Succesfully putted item, in: " << cell_type;
                                    //block->s_output.count = 0;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case South:
            if(world->checkBlock(x - 64, y)) { 
                bws block = dynamic_cast<bws>(world->getBlock(x - 64, y));

                if(block != NULL) {
                    GetItemResult getitemresult = block->get_item();
                    if(getitemresult.result != EMPTY && world->checkBlock(x + 64, y)) {
                        bws block1 = dynamic_cast<bws>(world->getBlock(x + 64, y));

                        if(block1 != NULL) {
                            CellType cell_type = block1->cell_priority(PUT);
                            if(cell_type != Null) {
                                Result result = block1->put_item(cell_type, getitemresult.item_id, 1);
                                if(result == SUCCESS) {
                                    //std::cout << "Succesfully putted item, in: " << cell_type;
                                    //block->s_output.count = 0;
                                }
                            }
                        }
                    }
                }
            }
            break;
        break;
        case East:
            if(world->checkBlock(x - 64, y)) { 
                bws block = dynamic_cast<bws>(world->getBlock(x - 64, y));

                if(block != NULL) {
                    GetItemResult getitemresult = block->get_item();
                    if(getitemresult.result != EMPTY && world->checkBlock(x + 64, y)) {
                        bws block1 = dynamic_cast<bws>(world->getBlock(x + 64, y));

                        if(block1 != NULL) {
                            CellType cell_type = block1->cell_priority(PUT);
                            if(cell_type != Null) {
                                Result result = block1->put_item(cell_type, getitemresult.item_id, 1);
                                if(result == SUCCESS) {
                                    //std::cout << "Succesfully putted item, in: " << cell_type;
                                    //block->s_output.count = 0;
                                }
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
};

Loader* CreateLoader(TextureManager *texturemanager, std::string EntityID, Direction _place_direction,float X, float Y) {
    Loader* loader = new Loader(texturemanager, EntityID, _place_direction, X, Y);
    return loader;
}

#endif