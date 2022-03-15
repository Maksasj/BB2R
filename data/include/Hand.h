/*
      Class for interactions with world from player side
*/

#ifndef HAND_CLASS_H
#define HAND_CLASS_H

#include "World.h"
#include "utilities/vector.h"
#include "ModLoader.h"
#include <raylib.h>
#include <string>
#include <cmath>

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

float distance(vec2 p1, vec2 p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
}

bool collis(BlockRect rect1, BlockRect rect2) {
       if ( rect1.x <= rect2.x + rect2.w &&
            rect1.x + rect1.w >= rect2.x &&
            rect1.y <= rect2.y + rect2.h &&
            rect1.h + rect1.y >= rect2.y) {
              return true;
      }
      return false;
}

std::string GetBlock(World* world, int x, int y) {
      int X = floor(x / 16); if (x < 0) { X--; }
      int Y = floor(y / 16); if (y < 0) { Y--; }
      
      std::string block = "nothing";

      int px = abs(X*16 - x);
      int py = abs(Y*16 - y);

      if (world->_World[{X,Y}]->block_exist[px][py]) {
            block = world->_World[{X,Y}]->blocks[px][py]->EntityID;
      }

      return block;
}

int GetConv_Sys(World* world, int x, int y) {
      int X = floor(x / 16); if (x < 0) { X--; }
      int Y = floor(y / 16); if (y < 0) { Y--; }
      
      int ret = 0;

      int px = abs(X*16 - x);
      int py = abs(Y*16 - y);
      
      if (world->_World[{X,Y}]->block_exist[px][py]) {
            ret = world->_World[{X,Y}]->blocks[px][py]->Get("conv_syst");
      }

      return ret;
}

int GetDirection(World* world, int x, int y) {
      int X = floor(x / 16); if (x < 0) { X--; }
      int Y = floor(y / 16); if (y < 0) { Y--; }
      
      int ret = 0;

      int px = abs(X*16 - x);
      int py = abs(Y*16 - y);
      
      if (world->_World[{X,Y}]->block_exist[px][py]) {
            ret = world->_World[{X,Y}]->blocks[px][py]->direction;
      }

      return ret;
}

void PlacePrototype(World* world, std::string _block_id, int place_direction, int X, int Y, int px, int py) {
      if(_block_id == "conveyor_block") {

            std::string x_yp1 = GetBlock(world, X*16 + px, Y*16 + py + 1); //Down
            std::string x_ym1 = GetBlock(world, X*16 + px, Y*16 + py - 1); //Up
            std::string xp1_y = GetBlock(world, X*16 + px + 1, Y*16 + py); //Right
            std::string xm1_y = GetBlock(world, X*16 + px - 1, Y*16 + py); //Left 

            if (x_yp1 != "conveyor_block" && x_ym1 != "conveyor_block" && xp1_y != "conveyor_block" && xm1_y != "conveyor_block") {
                  //Create Conveyor system
                  int conv_syst = world->conveyorsystemmanager.CreateSystem();

                  //Create conveyor
                  ConveyorBelt *tmp_conv = CreateConveyorBelt(world->worldgenerator->texturemanager, _block_id, conv_syst, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  world->_World[{X,Y}]->blocks[px][py] = tmp_conv;
                  world->conveyorsystemmanager.ConveyorSystems[conv_syst].addConveyorBelt(tmp_conv);

            } else {
                  bool create_new_conv_sys = false;
                  // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT
                  if(place_direction == 1 || place_direction == 2) {
                        if (x_yp1 == "conveyor_block" || x_ym1 == "conveyor_block" ) {

                              int conv_sys = GetConv_Sys(world, X*16 + px, Y*16 + py + 1);
                              if (conv_sys == 0) { conv_sys = GetConv_Sys(world, X*16 + px, Y*16 + py - 1); }
                                    
                              ConveyorBelt *tmp_conv = CreateConveyorBelt(world->worldgenerator->texturemanager, _block_id, conv_sys, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                              world->_World[{X,Y}]->blocks[px][py] = tmp_conv;
                              world->conveyorsystemmanager.ConveyorSystems[conv_sys].addConveyorBelt(tmp_conv);
                              
                        } else { create_new_conv_sys = true; }
                  } else if(place_direction == 3 || place_direction == 4) {
                        if (xp1_y == "conveyor_block" || xm1_y == "conveyor_block") {
                              int conv_sys = GetConv_Sys(world, X*16 + px + 1, Y*16 + py);
                              if (conv_sys == 0) { conv_sys = GetConv_Sys(world, X*16 + px - 1, Y*16 + py); }

                              ConveyorBelt *tmp_conv = CreateConveyorBelt(world->worldgenerator->texturemanager, _block_id, conv_sys, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                              world->_World[{X,Y}]->blocks[px][py] = tmp_conv;
                              world->conveyorsystemmanager.ConveyorSystems[conv_sys].addConveyorBelt(tmp_conv);
                        } else { create_new_conv_sys = true; }
                  }

                  //Create new conveyor system if not exist
                  if (create_new_conv_sys == true) {
                        //Create Conveyor system
                        int conv_syst = world->conveyorsystemmanager.CreateSystem();

                        //Create conveyor
                        ConveyorBelt *tmp_conv = CreateConveyorBelt(world->worldgenerator->texturemanager, _block_id, conv_syst, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                        world->_World[{X,Y}]->blocks[px][py] = tmp_conv;
                        world->conveyorsystemmanager.ConveyorSystems[conv_syst].addConveyorBelt(tmp_conv);
                  }
            }  
      } else {
            world->_World[{X,Y}]->blocks[px][py] = CreateBlock(world->worldgenerator->texturemanager, _block_id, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
      }
}

struct Hand
{     
      World *world;
      ModLoader *modloader;
      int place_direction;

      Hand(World *_world, ModLoader *_modloader) {
            world = _world; modloader = _modloader;
      }

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
            ItemEntity* tmp_item_entity = CreateItemEntity(world->worldgenerator->texturemanager, _item_id, count, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
            
            if (world->_World[{X,Y}]->block_exist[px][py]) {
                  if (world->_World[{X,Y}]->blocks[px][py]->EntityID == "conveyor_block") {
                        world->_World[{X,Y}]->blocks[px][py]->PickUpItem(tmp_item_entity);
                        world->_World[{X,Y}]->blocks[px][py]->locked = true;
                  }
            } else {
                  world->_World[{X,Y}]->items.push_back(tmp_item_entity);
            }
      }

      void TryDropItem(float Player_X, float Player_Y) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);

            DropItem("gem", 1, X, Y, px, py);
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
                  
                  PlacePrototype(world, _block_id, place_direction, X, Y, px, py);
                  
                  world->_World[{X,Y}]->block_exist[px][py] = true;
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