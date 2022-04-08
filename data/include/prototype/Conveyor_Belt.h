#ifndef CONVEYORBELT_CLASS_H
#define CONVEYORBELT_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Timer.h"
#include "../World/World.h"
#include "Block.h"
#include "../Texture/TextureManager.h"

struct ConveyorBelt : public Block
{    
    World *world;
    bool trans_cd;

    std::string item_holding = "nothing";
    float item_float = 0;

    vec2 item_step = {0, 0};

    int speed = 240;

    ConveyorBelt(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        locked = false;
        trans_cd = false;
        direction = _place_direction;
        
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() { // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT
        
        if (locked == true) {
            if (direction == 1) {
                item_step.y -= 64/(float)speed;
            } else if (direction == 2) {
                item_step.y += 64/(float)speed;
            } else if (direction == 3) {
                item_step.x -= 64/(float)speed;
            } else if (direction == 4) {
                item_step.x += 64/(float)speed;
            }

            if (trans_cd == false) {
                if (timer.step % speed == 0) {
                    if (direction == 1) { // UP
                        if(world->checkBlock(x, y - 64)) {
                            item_step = {0, 0};
                            Block *tmp_block = world->getBlock(x, y - 64);
                            if (tmp_block->EntityID == "conveyor_block" && tmp_block->locked == false) {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(tmp_block);
                                tmp_conv->locked = true; 
                                tmp_conv->trans_cd = true; 
                                tmp_conv->item_holding = item_holding;
                                locked = false;
                            } else {
                                item_step = {0, 0};
                            }
                        }
                    } else if (direction == 2) { // DOWN
                        if(world->checkBlock(x, y + 64)) {
                            item_step = {0, 0};
                            Block *tmp_block = world->getBlock(x, y + 64);
                            if (tmp_block->EntityID == "conveyor_block" && tmp_block->locked == false) {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(tmp_block);
                                tmp_conv->locked = true; 
                                tmp_conv->trans_cd = true; 
                                tmp_conv->item_holding = item_holding;
                                locked = false;
                            } else {
                                item_step = {0, 0};
                            }
                        }
                    } else if (direction == 3) { //LEFT
                        if(world->checkBlock(x - 64, y)) {
                            item_step = {0, 0};
                            Block *tmp_block = world->getBlock(x - 64, y);
                            if (tmp_block->EntityID == "conveyor_block" && tmp_block->locked == false) {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(tmp_block);
                                tmp_conv->locked = true; 
                                tmp_conv->trans_cd = true; 
                                tmp_conv->item_holding = item_holding;
                                locked = false;
                            } else {
                                item_step = {0, 0};
                            }
                        }
                    } else if (direction == 4) { //RIGHT
                        if(world->checkBlock(x + 64, y)) { 
                            item_step = {0, 0};
                            Block *tmp_block = world->getBlock(x + 64, y);
                            if (tmp_block->EntityID == "conveyor_block" && tmp_block->locked == false) {
                                ConveyorBelt* tmp_conv = dynamic_cast<ConveyorBelt*>(tmp_block);
                                tmp_conv->locked = true; 
                                tmp_conv->trans_cd = true; 
                                tmp_conv->item_holding = item_holding;
                                locked = false;
                            } else {
                                item_step = {0, 0};
                            }
                        }
                    }
                }
            }

            trans_cd = false;
        }
    }
    
    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);
        if (locked) {
            //DrawRectangleV({x - camera.x, y - camera.y}, {64, 64}, {255, 0, 0, 50});
            //DrawRectangleV({x - camera.x + item_step.x, y - camera.y + item_step.y}, {64, 64}, {0, 0, 255, 50});

            texturemanager->Textures[item_holding]->Render("idle", x - camera.x + item_step.x, y - camera.y + item_step.y);
        }
    }
};

ConveyorBelt* CreateConveyorBelt(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) {
    ConveyorBelt* belt = new ConveyorBelt(texturemanager, EntityID, _place_direction, X, Y);
    return belt;
}

#endif