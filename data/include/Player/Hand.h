/*
      Class for interactions with world from player side
*/

#ifndef HAND_CLASS_H
#define HAND_CLASS_H

#include <raylib.h>
#include <string>
#include <cmath>

//Tiles
#include "../Prototype/Farmland.h"

//Blocks
#include "../Prototype/Conveyor_Belt.h"
#include "../Prototype/Lamp.h"
#include "../Prototype/Campfire.h"
#include "../Prototype/Inserter.h"
#include "../Prototype/Drill.h"
#include "../Prototype/BlockWithStorage.h"
#include "../Prototype/CraftingMachine.h"
#include "../Prototype/Crop.h"

//Other
#include "../Prototype/Recipe.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Mod/ModLoader.h"

#include "PlacePrototype.h"

typedef struct Drop {
      std::string item_id;
      int count;
} Drop;

typedef struct BlockRect {
      float x;
      float y;
      float w;
      float h;
} BlockRect;

float distance(vec2 p1, vec2 p2) { return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0); }

bool collis(BlockRect rect1, BlockRect rect2) {
       if ( rect1.x <= rect2.x + rect2.w &&
            rect1.x + rect1.w >= rect2.x &&
            rect1.y <= rect2.y + rect2.h &&
            rect1.h + rect1.y >= rect2.y) {
              return true;
      }
      return false;
}

struct Hand
{     
      World *world;
      ModLoader *modloader;
      Direction place_direction;

      Hand(World *_world, ModLoader *_modloader) { world = _world; modloader = _modloader; }

      float GetSlipp(float Player_X, float Player_Y) {
            int X = floor((Player_X + 32) / CHUNK_SIZE);
            int Y = floor((Player_Y + 32) / CHUNK_SIZE);

            int px = abs(((Player_X + 32) - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs(((Player_Y + 32) - CHUNK_SIZE*Y)/TILE_SIZE);

            if(modloader->mods["base"]->TileData[world->_World[{X,Y}]->tiles[px][py]->EntityID].contains("slipperiness")) {
                  return modloader->mods["base"]->TileData[world->_World[{X,Y}]->tiles[px][py]->EntityID]["slipperiness"];
            }

            return 0.95;
      }

      bool TryPlaceBlock(float Player_X, float Player_Y, std::string _item_id) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);
            
            if(modloader->mods["base"]->ItemData[_item_id]["usage"].contains("place_result")) {
                  return !world->_World[{X,Y}]->block_exist[px][py];
            }
            return false;
      }

      bool TryBreakBlock(float Player_X, float Player_Y) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);

            if(world->_World[{X,Y}]->block_exist[px][py]) {
                  if(modloader->mods["base"]->BlockData[world->_World[{X,Y}]->blocks[px][py]->EntityID].contains("minable")) {
                        return true;
                  }
            }

            return false;
      }

      Drop TryPickUpItem(float Player_X, float Player_Y) {
            std::string item_id = "nothing"; int count = 0;

            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            auto item = world->_World[{X,Y}]->items.begin();
            while(item != world->_World[{X,Y}]->items.end()) {
                  if( distance({Player_X, Player_Y}, {(*item)->x, (*item)->y}) < 70.0) {
                        item_id = (*item)->EntityID;
                        count = (*item)->count;

                        item = world->_World[{X,Y}]->items.erase(item);
                        return {item_id, count};
                  } else { item++; }
            }

            return {item_id, count};
      }
      
      void DropItem(std::string _item_id, int count, int X, int Y, int px, int py) {
            if (world->_World[{X,Y}]->block_exist[px][py]) {
                  Block *tmp_block = world->_World[{X,Y}]->blocks[px][py];
                  if (tmp_block->prototype == "BlockWithStorage") {
                        BlockWithStorage* tmp_block = dynamic_cast<BlockWithStorage*>(world->_World[{X,Y}]->blocks[px][py]);
                        /*
                        if (tmp_block->locked == false) {
                              tmp_block->locked = true;
                              tmp_block->item_holding = _item_id;
                        }
                        */             
                  } else if (tmp_block->EntityID == "chest") {
                        //Something like drop in chest
                  } else {
                        ItemEntity* tmp_item_entity = CreateItemEntity(world->worldgenerator->texturemanager, _item_id, count, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                        world->_World[{X,Y}]->items.push_back(tmp_item_entity);
                        world->Chunks[{X,Y}] = world->_World[{X,Y}];
                  }
            } else {
                  ItemEntity* tmp_item_entity = CreateItemEntity(world->worldgenerator->texturemanager, _item_id, count, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  world->_World[{X,Y}]->items.push_back(tmp_item_entity);
                  world->Chunks[{X,Y}] = world->_World[{X,Y}];
            }
      }

      void TryDropItem(std::string item_id, float Player_X, float Player_Y) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);

            DropItem(item_id, 1, X, Y, px, py);
      }

      void BreakBlock(float Player_X, float Player_Y) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);;

            std::string item_id = "nothing"; int count = 0;

            if(modloader->mods["base"]->BlockData[world->_World[{X,Y}]->blocks[px][py]->EntityID].contains("minable")) {
                  if(modloader->mods["base"]->BlockData[world->_World[{X,Y}]->blocks[px][py]->EntityID]["minable"].contains("result")) {
                        item_id = modloader->mods["base"]->BlockData[world->_World[{X,Y}]->blocks[px][py]->EntityID]["minable"]["result"]["item"];
                        count = modloader->mods["base"]->BlockData[world->_World[{X,Y}]->blocks[px][py]->EntityID]["minable"]["result"]["count"];
                  }
            }

            if (item_id != "nothing") {
                  DropItem(item_id, count, X, Y, px, py);
            }

            delete world->_World[{X,Y}]->blocks[px][py];
            world->_World[{X,Y}]->block_exist[px][py] = false;
            world->Chunks[{X,Y}] = world->_World[{X,Y}];
      }

      void PlaceBlock(float Player_X, float Player_Y, std::string _item_id) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);

            std::string _block_id;

            if(modloader->mods["base"]->ItemData[_item_id]["usage"].contains("place_result")) {
                  _block_id = modloader->mods["base"]->ItemData[_item_id]["usage"]["place_result"];
            }

            if(world->_World[{X,Y}]->block_exist[px][py] == false) {
                  
                  PlacePrototype(world, modloader, _block_id, place_direction, X, Y, px, py);
            
                  world->Chunks[{X,Y}] = world->_World[{X,Y}];    
            }
      }

      void ChangeTile(float Player_X, float Player_Y, std::string _item_id) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);

            if(world->_World[{X,Y}]->tiles[px][py]->subgroup == "farmable_soil") {
                  Farmland* farmland = CreateFarmland(world->worldgenerator->texturemanager, "farmland", CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  
                  farmland->grow_multiplier = 1;
                  
                  world->_World[{X,Y}]->tiles[px][py] = farmland;
                  world->_World[{X,Y}]->tile_exist[px][py] = true;
                  world->Chunks[{X,Y}] = world->_World[{X,Y}];    
            }
      }

      //TODO: Implement checking for neighbor chunks
      bool TryWalk(vec2 player_cords) {
            int X = floor((player_cords.x + 32) / CHUNK_SIZE); int Y = floor((player_cords.y + 32) / CHUNK_SIZE);

            //Player origin point
            vec2 player_origin_point = {};
            if (modloader->mods["base"]->MobData["player"]["solid"].contains("origin_point")) { player_origin_point = {modloader->mods["base"]->MobData["player"]["solid"]["origin_point"][0], modloader->mods["base"]->MobData["player"]["solid"]["origin_point"][1]}; }
            
            //Iterate each block in chunk , and if it solid check collision
            //TODO: maybe change iterator, mauybe something like from start from player location
            for (int x = 0; x < 16; x++) {
                  for (int y = 0; y < 16; y++) {
                        if (world->_World[{X,Y}]->block_exist[x][y]) {
                              vec2 block_cords = {(float)(X*CHUNK_SIZE + x*TILE_SIZE), (float)(Y*CHUNK_SIZE + y*TILE_SIZE)};
                              if (distance(block_cords, player_cords) < 80.0) { // Check if block in 70p radius
                                    if(modloader->mods["base"]->BlockData[ world->_World[{X,Y}]->blocks[x][y]->EntityID].contains("solid")) {
                                          
                                          //Block origin point and rectangle
                                          vec2 block_origin_point = {0, 0};
                                          if (modloader->mods["base"]->BlockData[ world->_World[{X,Y}]->blocks[x][y]->EntityID]["solid"].contains("origin_point")) { block_origin_point = {modloader->mods["base"]->BlockData[ world->_World[{X,Y}]->blocks[x][y]->EntityID]["solid"]["origin_point"][0], modloader->mods["base"]->BlockData[ world->_World[{X,Y}]->blocks[x][y]->EntityID]["solid"]["origin_point"][1]}; }
                                          BlockRect block_rect = { block_cords.x + block_origin_point.x, block_cords.y + block_origin_point.y, modloader->mods["base"]->BlockData[ world->_World[{X,Y}]->blocks[x][y]->EntityID]["solid"]["collision_box"]["height"], modloader->mods["base"]->BlockData[ world->_World[{X,Y}]->blocks[x][y]->EntityID]["solid"]["collision_box"]["height"] };

                                          if (collis(block_rect, { player_cords.x + player_origin_point.x, player_cords.y + player_origin_point.y, modloader->mods["base"]->MobData["player"]["solid"]["collision_box"]["width"], modloader->mods["base"]->MobData["player"]["solid"]["collision_box"]["height"] })) { return false; }
                                    }
                              }
                        }
                  } 
            }
            return true;
      }
};

#endif