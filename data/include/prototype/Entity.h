#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <iostream>
#include <raylib.h>
#include <stdio.h>

#include "../Texture/TextureManager.h"
#include "../Texture/Texture.h"

#include "../Defines.h"

#include "../Player/Camera.h"
#include "../Player/Inventory.h"

#include "../Renderer/LightSystem.h"
#include "../Renderer/Shader.h"

struct Entity
{   
      //General
      float x, y;
      std::string EntityID;
      std::string EntityState;

      //Texture && Animation Data
      game::Texture* tex;
      TextureManager *texturemanager;

      //Inventory
      Inventory* inventory;

      Entity(TextureManager *_texturemanager, std::string _EntityID, float X, float Y) {
            EntityID = _EntityID;
            tex = _texturemanager->Textures[EntityID]; 
            texturemanager = _texturemanager;  
            EntityState = "idle";
            x = X; y = Y;
      }
      
      virtual ~Entity(){}

      virtual void GetLight(LightSystem *lightsystem) {};
      virtual void Render(Shader shader) {
            tex->Render(EntityState, x - camera.x, y - camera.y);
      }
};


#endif