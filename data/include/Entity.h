#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <iostream>
#include <raylib.h>
#include <stdio.h>

#include "Shader.h"

#include "TextureManager.h"
#include "Texture.h"
#include "Defines.h"
#include "Camera.h"
#include "Inventory.h"
#include "LightSystem.h"

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