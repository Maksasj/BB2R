#ifndef BLOCKWITHSTORAGE_CLASS_H
#define BLOCKWITHSTORAGE_CLASS_H

#include <iostream>
#include <raylib.h>

#include "ParticleGenerator.h"
#include "../Renderer/Shader.h"
#include "../Timer.h"
#include "../World/World.h"
#include "Block.h"
#include "../Texture/TextureManager.h"
#include "../Renderer/LightSystem.h"
#include "../Utilities/vector.h"

enum Result 
{   
    SUCCESS = 1, 
    FULL = 2,
};

enum CellType
{
    Input = 1,
    Output = 2,
    Storage = 3,

    Null = 0,
};

typedef struct Cell {
    std::string item_id;
    int count;
} Cell;

typedef struct StorageCells {
    int count;
    std::vector<Cell> cells;
} StorageCells;

typedef struct SingleCell {
    int count;
    std::string item_id;
} SingleCell;

struct BlockWithStorage : public Block
{
    bool single_item;

    StorageCells input;
    StorageCells output;
    StorageCells storage;

    SingleCell s_input;
    SingleCell s_output;
    SingleCell s_storage;

    BlockWithStorage(TextureManager *texturemanager, std::string EntityID, float X, float Y) : Block(texturemanager, EntityID, X, Y) {
        s_input.count = 0;
        s_output.count = 0;
        s_storage.count = 0;
    }

    Result put_item(CellType cell_type, std::string id, int count) {
        switch (cell_type)
        {
        case Input:
            //Input code
            if(!single_item) {
                for(auto cell : input.cells) {
                    if(cell.item_id == id) {
                        cell.count += count;
                        return SUCCESS;
                    }
                }
                return FULL;
            } else {
                if(count == 1 && s_input.count != 1) {
                    s_input.item_id = id;
                    s_input.count = 1;
                    return SUCCESS;
                }
                return FULL;
            }

            break;
        case Output:
            if(!single_item) {
                for(auto &cell : output.cells) {
                    if(cell.item_id == id) {
                        cell.count += count;
                        return SUCCESS;
                    }
                }
                return FULL;
            } else {
                if(s_output.count == 1) {
                    return FULL;
                }

                if(count == 1 && s_output.count != 1) {
                    s_output.item_id = id;
                    s_output.count = 1;
                    return SUCCESS;
                }
                return FULL;
            }
            
            break;
        case Storage:
            //Storage code
            if(!single_item) {
                for(auto &cell : storage.cells) {
                    if(cell.item_id == id) {
                        cell.count += count;
                        return SUCCESS;
                    }
                }
                return FULL;
            } else {

                if(count == 1 && s_storage.count != 1) {
                    s_storage.item_id = id;
                    s_storage.count = 1;
                    return SUCCESS;
                }
                return FULL;
            }

            break;
        
        default:
            break;
        }
    }
};

typedef BlockWithStorage* bws;

#endif