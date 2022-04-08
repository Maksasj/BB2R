#ifndef TEXTUREMANAGER_CLASS_H
#define TEXTUREMANAGER_CLASS_H

#include <iostream>
#include <map>
#include <stdio.h>

#include "../Mod/ModLoader.h"
#include "Texture.h"
#include "AnimationManager.h"

struct TextureManager
{   
    std::map<std::string, game::Texture*> Textures;
    AnimationManager *animationmanager;

    TextureManager(ModLoader *modloader) {
        animationmanager = new AnimationManager();
        modloader->LoadTextures(Textures, animationmanager);
    }

    void UpdateAnimations() {
        animationmanager->UpdateAnimation();
    }
};

#endif