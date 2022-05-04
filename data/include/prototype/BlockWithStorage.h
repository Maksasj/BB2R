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
    EMPTY = 3,
};

enum ActionType 
{   
    PUT = 1, 
    GET = 2,
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
    int count = 0;
} Cell;

typedef struct StorageCells {
    int count = 0;
    std::vector<Cell> cells;
} StorageCells;

typedef struct SingleCell {
    int count;
    std::string item_id;
} SingleCell;

typedef struct GetItemResult {
    Result result;
    std::string item_id;
} GetItemResult;

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

    //Write this function
    CellType cell_priority(ActionType action) {
        if(action == PUT) {
            if(input.count > 0) {
                return Input;
            }
        } else if(action == GET) {
            if(output.count > 0) {
                return Output;
            }
        }

        if(storage.count > 0) {
            return Storage;
        }
        
        return Null;
    }

    GetItemResult get_item() {
        if(!single_item) {

            if(output.count > 0) {
                for(auto item : output.cells) {
                    if(item.count > 0) {
                        return {SUCCESS, item.item_id};
                    }
                }

            } else if(storage.count > 0){
                for(auto item : storage.cells) {
                    if(item.count > 0) {
                        return {SUCCESS, item.item_id};
                    }
                }

            } else {
                return {EMPTY, ""};
            }
            
        } else {
            if(s_output.count > 0) {
                return {SUCCESS, s_output.item_id};
            } else if(s_storage.count > 0) {
                return {SUCCESS, s_output.item_id};
            } else {
                return {EMPTY, ""};
            }
        }
    }

    Result put_item(CellType cell_type, std::string id, int count) {
        switch (cell_type)
        {
        case Input:
            //Input code
            if(!single_item) {

                for(auto &cell : input.cells) {
                    if(cell.item_id == id) {
                        cell.count += count;
                        return SUCCESS;
                    }
                }

                if(input.cells.size() == 0) {
                    input.cells.push_back({id, count});
                    input.count++;
                    return SUCCESS;
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

                if(output.cells.size() == 0) {
                    output.cells.push_back({id, count});
                    output.count++;
                    return SUCCESS;
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

                if(storage.cells.size() == 0) {
                    storage.cells.push_back({id, count});
                    storage.count++;
                    return SUCCESS;
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