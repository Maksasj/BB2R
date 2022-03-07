/*
      Class for interactions with world from player side
*/

#ifndef HAND_CLASS_H
#define HAND_CLASS_H

#include "World.h"
#include "ModLoader.h"
#include <raylib.h>
#include <string>

struct Hand
{     
      World *world;
      ModLoader *modloader;

      Hand(World *_world, ModLoader *_modloader) {
            world = _world; modloader = _modloader;
      }

      bool TryPlaceBlock(float Player_X, float Player_Y, std::string _block_id) {
            int x = Player_X + (GetMousePosition().x - SCREEN_WIDTH/2) + 32;
            int y = Player_Y + (GetMousePosition().y - SCREEN_HEIGHT/2) + 32;

            int X = floor(x / CHUNK_SIZE);
            int Y = floor(y / CHUNK_SIZE);

            int px = abs((x - CHUNK_SIZE*X)/64);
            int py = abs((y - CHUNK_SIZE*Y)/64);

            return !world->_World[{X,Y}]->block_exist[px][py];
      }

      bool TryBreakBlock(float Player_X, float Player_Y) {
            int x = Player_X + (GetMousePosition().x - SCREEN_WIDTH/2) + 32;
            int y = Player_Y + (GetMousePosition().y - SCREEN_HEIGHT/2) + 32;

            int X = floor(x / CHUNK_SIZE);
            int Y = floor(y / CHUNK_SIZE);

            int px = abs((x - CHUNK_SIZE*X)/64);
            int py = abs((y - CHUNK_SIZE*Y)/64);

            return world->_World[{X,Y}]->block_exist[px][py];
      }

      std::string BreakBlock(float Player_X, float Player_Y) {
            int x = Player_X + (GetMousePosition().x - SCREEN_WIDTH/2) + 32;
            int y = Player_Y + (GetMousePosition().y - SCREEN_HEIGHT/2) + 32;

            int X = floor(x / CHUNK_SIZE);
            int Y = floor(y / CHUNK_SIZE);

            int px = abs((x - CHUNK_SIZE*X)/64);
            int py = abs((y - CHUNK_SIZE*Y)/64);
 
            std::string drop = "stone_wall"; //TODO FIX DROP SYSTEM

            delete world->_World[{X,Y}]->blocks[px][py];
            world->_World[{X,Y}]->block_exist[px][py] = false;
            world->Chunks[{X,Y}] = world->_World[{X,Y}];

            return drop;
      }

      void PlaceBlock(float Player_X, float Player_Y, std::string _block_id) {
            int x = Player_X + (GetMousePosition().x - SCREEN_WIDTH/2) + 32;
            int y = Player_Y + (GetMousePosition().y - SCREEN_HEIGHT/2) + 32;

            int X = floor(x / CHUNK_SIZE);
            int Y = floor(y / CHUNK_SIZE);

            int px = abs((x - CHUNK_SIZE*X)/64);
            int py = abs((y - CHUNK_SIZE*Y)/64); 

            if(world->_World[{X,Y}]->block_exist[px][py] == false) {
                  world->_World[{X,Y}]->blocks[px][py] = CreateBlock(world->worldgenerator->texturemanager, _block_id, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  world->_World[{X,Y}]->block_exist[px][py] = true;
                  world->Chunks[{X,Y}] = world->_World[{X,Y}];    
            }
      }
};

#endif