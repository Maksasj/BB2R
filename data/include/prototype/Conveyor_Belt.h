#ifndef CONVEYORBELT_CLASS_H
#define CONVEYORBELT_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Timer.h"
#include "../World/World.h"
#include "BlockWithStorage.h"
#include "../Texture/TextureManager.h"

typedef Block bl;

struct ConveyorBelt : public BlockWithStorage
{    
    typedef ConveyorBelt cb;

    World *world;

    int speed = 240;
    bool trans_cd = false;

    ConveyorBelt(TextureManager *texturemanager, std::string EntityID, Direction _place_direction, float X, float Y) : BlockWithStorage(texturemanager, EntityID, X, Y) {
        direction = _place_direction;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
        /*
        if(s_storage.count == 1 && timer.step % speed == 0 && trans_cd == false) {
            switch (direction)
            {
            case North:
                if(world->checkBlock(x, y - 64)) { 
                    bl *tmp_block = world->getBlock(x, y - 64);
                    if(tmp_block->prototype == "Conveyor") {
                        cb* tmp_conv = dynamic_cast<cb*>(world->getBlock(x, y - 64));                            
                        Result result = tmp_conv->put_item(Storage, s_storage.item_id, 1);
                        
                        if(result == SUCCESS) {
                            s_storage.count = 0;
                            tmp_conv->trans_cd = true;
                        }
                    }
                }
                break;

            case South:
                if(world->checkBlock(x, y + 64)) { 
                    bl *tmp_block = world->getBlock(x, y + 64);
                    if(tmp_block->prototype == "Conveyor") {
                        cb* tmp_conv = dynamic_cast<cb*>(world->getBlock(x, y + 64));                            
                        Result result = tmp_conv->put_item(Storage, s_storage.item_id, 1);
                    
                        if(result == SUCCESS) {
                            s_storage.count = 0;
                            tmp_conv->trans_cd = true;
                        }
                    }
                }
                break;

            case West:
                if(world->checkBlock(x - 64, y)) { 
                    bl *tmp_block = world->getBlock(x - 64, y);
                    if(tmp_block->prototype == "Conveyor") {
                        cb* tmp_conv = dynamic_cast<cb*>(world->getBlock(x - 64, y));                            
                        Result result = tmp_conv->put_item(Storage, s_storage.item_id, 1);
                        
                        if(result == SUCCESS) {
                            s_storage.count = 0;
                            tmp_conv->trans_cd = true;
                        }
                    }
                }
                break;

            case East:
                if(world->checkBlock(x + 64, y)) { 
                    bl *tmp_block = world->getBlock(x + 64, y);
                    if(tmp_block->prototype == "Conveyor") {
                        cb* tmp_conv = dynamic_cast<cb*>(world->getBlock(x + 64, y));                            
                        Result result = tmp_conv->put_item(Storage, s_storage.item_id, 1);
                        
                        if(result == SUCCESS) {
                            s_storage.count = 0;
                            tmp_conv->trans_cd = true;
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
        */
        trans_cd = false;
    }
    
    void Render(Shader shader) {
        tex->Render(EntityState, x - camera.x, y - camera.y);

        if (s_storage.count == 1)
            texturemanager->Textures[s_storage.item_id]->Render("idle", x - camera.x, y - camera.y);
    }
};

ConveyorBelt* CreateConveyorBelt(TextureManager *texturemanager, std::string EntityID, Direction _place_direction, float X, float Y) {
    ConveyorBelt* belt = new ConveyorBelt(texturemanager, EntityID, _place_direction, X, Y);
    return belt;
}

#endif