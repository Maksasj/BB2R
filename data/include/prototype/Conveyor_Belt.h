#ifndef CONVEYORBELT_CLASS_H
#define CONVEYORBELT_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Block.h"
#include "../TextureManager.h"

struct ConveyorBelt : public Block
{    
    ItemEntity *item;

    int conv_syst;

    ConveyorBelt (TextureManager *texturemanager, std::string EntityID, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        locked = false;
    }

    void Update() {

    }

    void PickUpItem(ItemEntity *_item) {
        item = _item;
    };

    int Get(std::string id) {
        if (id == "conv_syst") { 
            return conv_syst;
        }
    };

    void Render() {
        tex->Render(EntityState, x - camera.x, y - camera.y);
        if (locked) {
            DrawRectangleV({x - camera.x, y - camera.y}, {64, 64}, {255, 0, 0, 100});
            item->Render();
        } else {
            DrawRectangleV({x - camera.x, y - camera.y}, {64, 64}, {0, 255, 0, 100});
        }

        DrawRectangleV({x - camera.x, y - camera.y}, {16, 16}, {static_cast<unsigned char>(50*conv_syst), static_cast<unsigned char>(50*conv_syst), 0, 255});
    
        if (direction == 1) {
            DrawRectangleV({x - camera.x + 24, y - camera.y}, {16, 16}, {0, 0, 0, 255});
        } else if (direction == 2) {
            DrawRectangleV({x - camera.x + 24, y - camera.y}, {16, 16}, {255, 0, 0, 255});
        } else if (direction == 3) {
            DrawRectangleV({x - camera.x + 24, y - camera.y}, {16, 16}, {0, 255, 0, 255});
        } else if (direction == 4) {
            DrawRectangleV({x - camera.x + 24, y - camera.y}, {16, 16}, {0, 0, 255, 255});
        }
    
    }
};

ConveyorBelt* CreateConveyorBelt(TextureManager *texturemanager, std::string EntityID, float X, float Y) {
    ConveyorBelt* belt = new ConveyorBelt(texturemanager, EntityID, X, Y);
    return belt;
}

#endif