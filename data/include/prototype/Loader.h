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
    int speed;

    Loader(TextureManager *texturemanager, std::string EntityID, int _place_direction, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        direction = _place_direction;
    }

    void SetupWorld(void *p) {
        world = static_cast<World*>(p);
    }

    void Update() {
        if (direction == 1) { // UP
            if(world->checkBlock(x - 64, y)) { 
                BlockWithStorage* tml_b_s = dynamic_cast<BlockWithStorage*>(world->getBlock(x - 64, y));

                if(tml_b_s != NULL) {
                    if(tml_b_s->locked == true && world->checkBlock(x + 64, y)) {
                        BlockWithStorage* tml_b_s1 = dynamic_cast<BlockWithStorage*>(world->getBlock(x + 64, y));
                        if(tml_b_s1 != NULL) {
                        
                            if(!tml_b_s1->locked) {
                                tml_b_s1->item_holding = tml_b_s->item_holding;
                                tml_b_s1->locked = true;
                                tml_b_s->locked = false;

                                std::cout << "Transported Item: "+tml_b_s1->item_holding+"\n";
                            }
                            
                        }
                    }
                }
            }
        } else if (direction == 2) { // DOWN
            if(world->checkBlock(x + 64, y)) { 
                BlockWithStorage* tml_b_s = dynamic_cast<BlockWithStorage*>(world->getBlock(x + 64, y));

                if(tml_b_s != NULL) {
                    if(tml_b_s->locked == true && world->checkBlock(x - 64, y)) { 
                        BlockWithStorage* tml_b_s1 = dynamic_cast<BlockWithStorage*>(world->getBlock(x - 64, y));
                        if(tml_b_s1 != NULL) {
                            if(tml_b_s1->locked) {
                                tml_b_s1->item_holding = tml_b_s->item_holding;
                                tml_b_s1->locked = true;
                                tml_b_s->locked = false;

                                std::cout << "Transported Item: "+tml_b_s1->item_holding+"\n";
                            }
                        }
                    }
                }
            }
        } else if (direction == 3) { //LEFT
            if(world->checkBlock(x, y - 64)) { 
                BlockWithStorage* tml_b_s = dynamic_cast<BlockWithStorage*>(world->getBlock(x, y - 64));

                if(tml_b_s != NULL) {
                    if(tml_b_s->locked == true && world->checkBlock(x, y + 64)) { 
                        BlockWithStorage* tml_b_s1 = dynamic_cast<BlockWithStorage*>(world->getBlock(x, y + 64));
                        if(tml_b_s1 != NULL) {
                            if(tml_b_s1->locked) {
                                tml_b_s1->item_holding = tml_b_s->item_holding;
                                tml_b_s1->locked = true;
                                tml_b_s->locked = false;

                                std::cout << "Transported Item: "+tml_b_s1->item_holding+"\n";
                            }
                        }
                    }
                }
            }
        } else if (direction == 4) { //RIGHT
             if(world->checkBlock(x, y + 64)) { 
                BlockWithStorage* tml_b_s = dynamic_cast<BlockWithStorage*>(world->getBlock(x, y + 64));

                if(tml_b_s != NULL) {
                    if(tml_b_s->locked == true && world->checkBlock(x, y - 64)) { 
                        BlockWithStorage* tml_b_s1 = dynamic_cast<BlockWithStorage*>(world->getBlock(x, y - 64));
                        if(tml_b_s1 != NULL) {
                            if(tml_b_s1->locked) {
                                tml_b_s1->item_holding = tml_b_s->item_holding;
                                tml_b_s1->locked = true;
                                tml_b_s->locked = false;

                                std::cout << "Transported Item: "+tml_b_s1->item_holding+"\n";
                            }
                        }
                    }
                }
            }
        }
    }
};

Loader* CreateLoader(TextureManager *texturemanager, std::string EntityID, int _place_direction,float X, float Y) {
    Loader* loader = new Loader(texturemanager, EntityID, _place_direction, X, Y);
    return loader;
}

#endif