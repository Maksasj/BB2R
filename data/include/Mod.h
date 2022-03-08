#ifndef MOD_CLASS_H
#define MOD_CLASS_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <json.h>
#include <map>

#include "utilities/files_in_directory.h"

#include "TextureManager.h"
#include "Texture.h"
#include "AnimationManager.h"

struct Mod
{   
    std::string mod_id;

    std::map<std::string, nlohmann::json> TileData;
    std::map<std::string, nlohmann::json> BlockData;
    std::vector<nlohmann::json> MobData;
    std::map<std::string, nlohmann::json> ItemData;

    std::vector<std::string> tile_file_array;
    std::vector<std::string> block_file_array;
    std::vector<std::string> mob_file_array;
    std::vector<std::string> item_file_array;
    
    std::vector<std::string> biomes_file_array;
    std::map<std::string , nlohmann::json> WorldGeneratorData;
    
    std::vector<std::string> planettypes_file_array;
    std::map<std::string , nlohmann::json> PlanetTypeData;

      Mod(std::string _mod_id) {
            mod_id = _mod_id;
            
            tile_file_array = files_in_directory("data/mods/"+mod_id+"/tiles");
            block_file_array = files_in_directory("data/mods/"+mod_id+"/blocks");
            mob_file_array = files_in_directory("data/mods/"+mod_id+"/mobs");
            item_file_array = files_in_directory("data/mods/"+mod_id+"/items");

            biomes_file_array = files_in_directory("data/mods/"+mod_id+"/world_generation/biomes");
            planettypes_file_array = files_in_directory("data/mods/"+mod_id+"/world_generation/planet_types");
      }

      void LoadMod() {
            //Tiles
            for (auto tile_path : tile_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/tiles/" + tile_path);
                  nlohmann::json TileData_tmp = nlohmann::json::parse(ifs);
                  TileData[TileData_tmp["id"]] = TileData_tmp;
                  ifs.close();
            }

            //Blocks
            for (auto block_path : block_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/blocks/" + block_path);
                  nlohmann::json BlockData_tmp = nlohmann::json::parse(ifs);
                  BlockData[BlockData_tmp["id"]] = BlockData_tmp;
                  ifs.close();
            }

            //Mobs
            for (auto mobs_path : mob_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/mobs/" + mobs_path);
                  nlohmann::json MobData_tmp = nlohmann::json::parse(ifs);
                  MobData.push_back(MobData_tmp);
                  ifs.close();
            }

            //Items
            for (auto item_path : item_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/items/" + item_path);
                  nlohmann::json ItemData_tmp = nlohmann::json::parse(ifs);
                  ItemData[ItemData_tmp["id"]] = ItemData_tmp;
                  ifs.close();
            }

            //Biomes
            for (auto biome_path : biomes_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/world_generation/biomes/" + biome_path);
                  nlohmann::json BiomeData_tmp = nlohmann::json::parse(ifs);
                  WorldGeneratorData[BiomeData_tmp["id"]] = BiomeData_tmp;
                  ifs.close();
            }
            
            //Planet Types
            for (auto planettype_path : planettypes_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/world_generation/planet_types/" + planettype_path);
                  nlohmann::json PlanetTypeData_tmp = nlohmann::json::parse(ifs);
                  PlanetTypeData[PlanetTypeData_tmp["id"]] = PlanetTypeData_tmp;
                  ifs.close();
            }
      }
    
      void LoadTextures(std::map<std::string, game::Texture*> &Textures, AnimationManager* animationmanager) {
            //Tile
            for (auto tile : TileData) {
                  std::string _path = tile.second["texture"]["path"];
                  Textures[tile.second["id"]] = new game::Texture("data/mods/"+mod_id+"/"+_path, tile.second["texture"]["size"]["width"], tile.second["texture"]["size"]["height"]);
                  
                  if(tile.second["texture"].contains("animation")) {
                        for (auto& animation : tile.second["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[tile.second["id"]], tile.second["texture"]["animation"][animation.key()]["row"], tile.second["texture"]["animation"][animation.key()]["collum"], tile.second["texture"]["animation"][animation.key()]["speed"], tile.second["texture"]["animation"][animation.key()]["frame_size"]["width"], tile.second["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
                  
            }
            
            //Blocks
            for (auto block : BlockData) {
                  std::string _path = block.second["texture"]["path"];
                  Textures[block.second["id"]] = new game::Texture("data/mods/"+mod_id+"/"+_path, block.second["texture"]["size"]["width"], block.second["texture"]["size"]["height"]);
                  
                  if(block.second["texture"].contains("animation")) {
                        for (auto& animation : block.second["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[block.second["id"]], block.second["texture"]["animation"][animation.key()]["row"], block.second["texture"]["animation"][animation.key()]["collum"], block.second["texture"]["animation"][animation.key()]["speed"], block.second["texture"]["animation"][animation.key()]["frame_size"]["width"], block.second["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
            }

            //Mobs
            for (auto mob : MobData) {
                  std::string _path = mob["texture"]["path"];
                  Textures[mob["id"]] = new game::Texture("data/mods/"+mod_id+"/"+_path, mob["texture"]["size"]["width"], mob["texture"]["size"]["height"]);
                  
                  if(mob["texture"].contains("animation")) {
                        for (auto& animation : mob["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[mob["id"]], mob["texture"]["animation"][animation.key()]["row"], mob["texture"]["animation"][animation.key()]["collum"], mob["texture"]["animation"][animation.key()]["speed"], mob["texture"]["animation"][animation.key()]["frame_size"]["width"], mob["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
            }

            //Items
            for (auto item : ItemData) {
                  std::string _path = item.second["texture"]["path"];
                  Textures[item.second["id"]] = new game::Texture("data/mods/"+mod_id+"/"+_path, item.second["texture"]["size"]["width"], item.second["texture"]["size"]["height"]);
                  
                  if(item.second["texture"].contains("animation")) {
                        for (auto& animation : item.second["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[item.second["id"]], item.second["texture"]["animation"][animation.key()]["row"], item.second["texture"]["animation"][animation.key()]["collum"], item.second["texture"]["animation"][animation.key()]["speed"], item.second["texture"]["animation"][animation.key()]["frame_size"]["width"], item.second["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
            }
      }
};




#endif