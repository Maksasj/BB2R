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
#include "../Prototype/Loader.h"

//Other
#include "../Prototype/Recipe.h"

#include "../World/World.h"
#include "../Utilities/vector.h"
#include "../Mod/ModLoader.h"

void PlacePrototype(World* world, ModLoader *_modloader, std::string _block_id, int place_direction, int X, int Y, int px, int py) {
      std::string prototype = "nothing";
      
      if (_modloader->mods["base"]->BlockData[_block_id].contains("prototype")) {
            prototype = _modloader->mods["base"]->BlockData[_block_id]["prototype"];
            std::cout << prototype << "\n";

            if(prototype == "Conveyor") {
                  ConveyorBelt *tmp_conv = CreateConveyorBelt(world->worldgenerator->texturemanager, _block_id, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  tmp_conv->prototype = "Conveyor";
                  tmp_conv->SetupWorld(world);

                  if (place_direction == 1) { tmp_conv->EntityState = "conveyor_block_up"; } else 
                  if (place_direction == 2) { tmp_conv->EntityState = "conveyor_block_down"; } else 
                  if (place_direction == 3) { tmp_conv->EntityState = "conveyor_block_left"; } else 
                  if (place_direction == 4) { tmp_conv->EntityState = "conveyor_block_right"; }

                  world->_World[{X,Y}]->blocks[px][py] = tmp_conv;
                  world->_World[{X,Y}]->block_exist[px][py] = true;

            } else if(prototype == "Drill") {
                  Drill *tmp_drill = CreateDrill(world->worldgenerator->texturemanager, _block_id, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  int drill_speed = _modloader->mods["base"]->BlockData[_block_id]["mining"]["mining_speed"];
                  int drill_hardness = _modloader->mods["base"]->BlockData[_block_id]["mining"]["hardness"];

                  tmp_drill->SetupWorld(world);
                  tmp_drill->Speed = drill_speed;
                  tmp_drill->hardness = drill_hardness;

                  if (place_direction == 1) { tmp_drill->EntityState = "drill_block_up"; } else 
                  if (place_direction == 2) { tmp_drill->EntityState = "drill_block_down"; } else 
                  if (place_direction == 3) { tmp_drill->EntityState = "drill_block_left"; } else 
                  if (place_direction == 4) { tmp_drill->EntityState = "drill_block_right"; }

                  world->_World[{X,Y}]->blocks[px][py] = tmp_drill;
                  world->_World[{X,Y}]->block_exist[px][py] = true;

            } else if(prototype == "Loader") {
                  Loader *tmp_loader = CreateLoader(world->worldgenerator->texturemanager, _block_id, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);

                  tmp_loader->SetupWorld(world);

                  if (place_direction == 1) { tmp_loader->EntityState = "loader_block_up"; } else 
                  if (place_direction == 2) { tmp_loader->EntityState = "loader_block_down"; } else 
                  if (place_direction == 3) { tmp_loader->EntityState = "loader_block_left"; } else 
                  if (place_direction == 4) { tmp_loader->EntityState = "loader_block_right"; }

                  world->_World[{X,Y}]->blocks[px][py] = tmp_loader;
                  world->_World[{X,Y}]->block_exist[px][py] = true;

            } else if(prototype == "Inserter") {
                  Inserter *tmp_inserter = CreateInserter(world->worldgenerator->texturemanager, _block_id, place_direction, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  tmp_inserter->SetupWorld(world);

                  if (place_direction == 1) { tmp_inserter->EntityState = "inserter_block_up"; } else 
                  if (place_direction == 2) { tmp_inserter->EntityState = "inserter_block_down"; } else 
                  if (place_direction == 3) { tmp_inserter->EntityState = "inserter_block_left"; } else 
                  if (place_direction == 4) { tmp_inserter->EntityState = "inserter_block_right"; }

                  world->_World[{X,Y}]->blocks[px][py] = tmp_inserter;
                  world->_World[{X,Y}]->block_exist[px][py] = true;

            } else if(prototype == "Lamp") {
                  Lamp* tmp_lamp = CreateLamp(world->worldgenerator->texturemanager, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  
                  world->_World[{X,Y}]->blocks[px][py] = tmp_lamp;
                  world->_World[{X,Y}]->block_exist[px][py] = true;
                  
            } else if(prototype == "Plant") {

                  if(world->_World[{X,Y}]->tiles[px][py]->EntityID == "farmland") {
                        Crop* tmp_crop = CreateCrop(world->worldgenerator->texturemanager, _block_id, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                        world->_World[{X,Y}]->blocks[px][py] = tmp_crop;
                        world->_World[{X,Y}]->block_exist[px][py] = true;

                  } 
            }  else if(prototype == "CraftingMachine") {
                  Recipe recipe;
                  std::string recipe_str = _modloader->mods["base"]->BlockData[_block_id]["crafting"]["fixed_recipe"];

                  CraftingMachine* craftingmachine = CreateCraftingMachine(world->worldgenerator->texturemanager, _block_id, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  
                  for(auto item : _modloader->mods["base"]->RecipeData[recipe_str]["recipe"]["ingredients"]) {
                        ItemRecipe itemrecipe;
                        itemrecipe.item = { item["item"] };
                        itemrecipe.count = { item["quantity"] };
                        recipe.ingredients.push_back(itemrecipe);
                  }
            
                  recipe.result.id = _modloader->mods["base"]->RecipeData[recipe_str]["recipe"]["result"]["item"];

                  craftingmachine->Recipe = recipe;
                  craftingmachine->Speed = (int)_modloader->mods["base"]->BlockData[_block_id]["crafting"]["crafting_speed"];
                  craftingmachine->single_item = true;


                  world->_World[{X,Y}]->blocks[px][py] = craftingmachine;
                  world->_World[{X,Y}]->block_exist[px][py] = true;

            } else if(prototype == "Campfire") {
                  Campfire* tmp_campfire = CreateCampfire(world->worldgenerator->texturemanager, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
                  
                  world->_World[{X,Y}]->blocks[px][py] = tmp_campfire;
                  world->_World[{X,Y}]->block_exist[px][py] = true;
            }
      } else {
            world->_World[{X,Y}]->blocks[px][py] = CreateBlock(world->worldgenerator->texturemanager, _block_id, CHUNK_SIZE*X + px*TILE_SIZE, CHUNK_SIZE*Y + py*TILE_SIZE);
            world->_World[{X,Y}]->block_exist[px][py] = true;
      }
}