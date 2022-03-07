#ifndef MOD_CLASS_H
#define MOD_CLASS_H

#include <iostream>
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

    std::vector<nlohmann::json> TileData;
    std::vector<nlohmann::json> BlockData;
    std::vector<nlohmann::json> MobData;
    std::vector<nlohmann::json> ItemData;

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
                  TileData.push_back(TileData_tmp);
                  ifs.close();
            }

            //Blocks
            for (auto block_path : block_file_array) {
                  std::ifstream ifs("data/mods/"+mod_id+"/blocks/" + block_path);
                  nlohmann::json BlockData_tmp = nlohmann::json::parse(ifs);
                  BlockData.push_back(BlockData_tmp);
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
                  ItemData.push_back(ItemData_tmp);
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
                  Textures[tile["id"]] = new game::Texture(tile["texture"]["path"], tile["texture"]["size"]["width"], tile["texture"]["size"]["height"]);
                  
                  if(tile["texture"].contains("animation")) {
                        for (auto& animation : tile["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[tile["id"]], tile["texture"]["animation"][animation.key()]["row"], tile["texture"]["animation"][animation.key()]["collum"], tile["texture"]["animation"][animation.key()]["speed"], tile["texture"]["animation"][animation.key()]["frame_size"]["width"], tile["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
                  
            }
            
            //Blocks
            for (auto block : BlockData) {
                  Textures[block["id"]] = new game::Texture(block["texture"]["path"], block["texture"]["size"]["width"], block["texture"]["size"]["height"]);
                  
                  if(block["texture"].contains("animation")) {
                        for (auto& animation : block["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[block["id"]], block["texture"]["animation"][animation.key()]["row"], block["texture"]["animation"][animation.key()]["collum"], block["texture"]["animation"][animation.key()]["speed"], block["texture"]["animation"][animation.key()]["frame_size"]["width"], block["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
            }

            //Mobs
            for (auto mob : MobData) {
                  Textures[mob["id"]] = new game::Texture(mob["texture"]["path"], mob["texture"]["size"]["width"], mob["texture"]["size"]["height"]);
                  
                  if(mob["texture"].contains("animation")) {
                        for (auto& animation : mob["texture"]["animation"].items()) {
                              animationmanager->AddAnimation(animation.key(), Textures[mob["id"]], mob["texture"]["animation"][animation.key()]["row"], mob["texture"]["animation"][animation.key()]["collum"], mob["texture"]["animation"][animation.key()]["speed"], mob["texture"]["animation"][animation.key()]["frame_size"]["width"], mob["texture"]["animation"][animation.key()]["frame_size"]["height"]);
                        }
                  }
            }
      }
};




#endif