#ifndef CONVEYORBELT_CLASS_H
#define CONVEYORBELT_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Timer.h"
#include "../World/World.h"
#include "BlockWithStorage.h"
#include "../Texture/TextureManager.h"

struct ConveyorBelt : public BlockWithStorage
{    
    World *world;
    bool trans_cd;

    int speed = 240;

    ConveyorBelt(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
        direction = _place_direction;

        trans_cd = false;
        locked = false;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() { // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT
        if(timer.step % speed == 0) {
            if (locked == true) {
                if (trans_cd == false) {
               
                    if (direction == 1) { // UP
                        if(world->checkBlock(x, y - 64)) { 
                            Block *tmp_block = world->getBlock(x, y - 64);
                            if(tmp_block->prototype == "Conveyor") {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(world->getBlock(x, y - 64));
                                
                                if(tmp_conv->locked == false) {
                                    tmp_conv->locked = true;
                                    tmp_conv->trans_cd = true;
                                    tmp_conv->item_holding = item_holding;
                                    locked = false;
                                }
                            }
                        }
                    } else if (direction == 2) { // DOWN
                        if(world->checkBlock(x, y + 64)) { 
                            Block *tmp_block = world->getBlock(x, y + 64);
                            if(tmp_block->prototype == "Conveyor") {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(world->getBlock(x, y + 64));
                                
                                if(tmp_conv->locked == false) {
                                    tmp_conv->locked = true;
                                    tmp_conv->trans_cd = true;
                                    tmp_conv->item_holding = item_holding;
                                    locked = false;
                                }
                            }
                        }
                    } else if (direction == 3) { //LEFT
                        if(world->checkBlock(x - 64, y)) { 
                            Block *tmp_block = world->getBlock(x - 64, y);
                            if(tmp_block->prototype == "Conveyor") {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(world->getBlock(x - 64, y));
                                
                                if(tmp_conv->locked == false) {
                                    tmp_conv->locked = true;
                                    tmp_conv->trans_cd = true;
                                    tmp_conv->item_holding = item_holding;
                                    locked = false;
                                }
                            }
                        }
                    } else if (direction == 4) { //RIGHT
                        if(world->checkBlock(x + 64, y)) { 
                            Block *tmp_block = world->getBlock(x + 64, y);
                            if(tmp_block->prototype == "Conveyor") {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(world->getBlock(x + 64, y));
                                
                                if(tmp_conv->locked == false) {
                                    tmp_conv->locked = true;
                                    tmp_conv->trans_cd = true;
                                    tmp_conv->item_holding = item_holding;
                                    locked = false;
                                }
                            }
                        }
                    }
                } else {
                    trans_cd = false;
                }
            }
        }
    }
    
    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);

        if (locked) {
            //DrawRectangleV({x - camera.x, y - camera.y}, {64, 64}, {255, 0, 0, 50});
            //DrawRectangleV({x - camera.x + item_step.x, y - camera.y + item_step.y}, {64, 64}, {0, 0, 255, 50});

            texturemanager->Textures[item_holding]->Render("idle", x - camera.x, y - camera.y);
        }
    }
};

ConveyorBelt* CreateConveyorBelt(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) {
    ConveyorBelt* belt = new ConveyorBelt(texturemanager, EntityID, _place_direction, X, Y);
    return belt;
}

#endif