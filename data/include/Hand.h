/*
      Class for interactions with world from player side
*/

#ifndef HAND_CLASS_H
#define HAND_CLASS_H

#include "World.h"
#include "ModLoader.h"
#include <raylib.h>
#include <string>

typedef struct Drop {
      std::string item_id;
      int count;
} Drop;

struct Hand
{     
      World *world;
      ModLoader *modloader;

      Hand(World *_world, ModLoader *_modloader) {
            world = _world; modloader = _modloader;
      }

      bool TryPlaceBlock(float Player_X, float Player_Y, std::string _block_id) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);
            
            return !world->_World[{X,Y}]->block_exist[px][py];
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

      Drop BreakBlock(float Player_X, float Player_Y) {
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

            delete world->_World[{X,Y}]->blocks[px][py];
            world->_World[{X,Y}]->block_exist[px][py] = false;
            world->Chunks[{X,Y}] = world->_World[{X,Y}];

            return {item_id, count};
      }

      void PlaceBlock(float Player_X, float Player_Y, std::string _block_id) {
            int ox = Player_X + (GetMousePosition().x + 32 - HALF_SCREEN_WIDTH);
            int oy = Player_Y + (GetMousePosition().y + 32 - HALF_SCREEN_HEIGHT);

            int X = floor(ox / CHUNK_SIZE); if (ox < 0) { X--; }
            int Y = floor(oy / CHUNK_SIZE); if (oy < 0) { Y--; }

            int px = abs((ox - CHUNK_SIZE*X)/TILE_SIZE);
            int py = abs((oy - CHUNK_SIZE*Y)/TILE_SIZE);

            if(world->_World[{X,Y}]->block_exist[px][py] == false) {
                  world->_World[{X,Y}]->blocks[px][py] = CreateBlock(world->worldgenerator->texturemanager, _block_id, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  world->_World[{X,Y}]->block_exist[px][py] = true;
                  world->Chunks[{X,Y}] = world->_World[{X,Y}];    
            }
      }
};

#endif