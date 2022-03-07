#ifndef BIOMEMANAGER_CLASS_H
#define BIOMEMANAGER_CLASS_H

#include <vector>
#include <iostream>
#include <string>
#include <json.h>

#include "ModLoader.h"
#include "Biome.h"

struct BiomeManager 
{
      std::vector<Biome*> Biomes;
      std::string fill_biome;
      float noise_size;

      BiomeManager() {
            noise_size = 0.6;
      }

      void LoadBiomes(ModLoader *_modloader, std::string planet_type) {
            for (auto planet_t : _modloader->mods["base"]->PlanetTypeData) {
                  if (planet_t.second["id"] == planet_type) {
                        fill_biome = planet_t.second["fill_biome"];

                        for (auto biome : _modloader->mods["base"]->WorldGeneratorData) {
                              bool if_correct_biome = false;
                              for (auto tmp_biome : planet_t.second["biomes"]) { if (tmp_biome == biome.first) { if_correct_biome = true; break; } }

                              if (if_correct_biome) { 
                                    Biome *tmp_biome = new Biome(biome.first, biome.second["temperature"]["max"], biome.second["temperature"]["min"], biome.second["humidity"]["max"], biome.second["humidity"]["min"], biome.second["hight_map"]["max"], biome.second["hight_map"]["min"], biome.second["hight_layer"]);
                                    
                                    for ( auto &mol : biome.second["blocks"].get<nlohmann::json::object_t>() ) {
                                          std::pair<std::string, float> block;
                                          block.first = mol.first; block.second = mol.second;
                                          tmp_biome->blocks.push_back(block);
                                    }
                                    Biomes.push_back(tmp_biome);
                              }
                        }
                        break;
                  }
            }     
      }
};

#endif