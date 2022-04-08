#ifndef MODLOADER_CLASS_H
#define MODLOADER_CLASS_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <json.h>

#include "../Utilities/files_in_directory.h"
//#include "utilities/folders_in_directory.h"
#include "Mod.h"

struct ModLoader
{   
      std::map<std::string, Mod*> mods;

      ModLoader() {
            Mod *tmp_mod = new Mod("base");
            tmp_mod->LoadMod();
            mods["base"] = tmp_mod;
      }

      void LoadTextures(std::map<std::string, game::Texture*> &Textures, AnimationManager* animationmanager) {
            for(auto mod : mods) {
                  std::cout << "Loading '"+mod.first+"' mod textures" << std::endl;
                  mod.second->LoadTextures(Textures, animationmanager);
            }
      }
};


#endif