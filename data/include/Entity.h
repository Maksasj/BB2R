#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <iostream>
#include <stdio.h>

#include "TextureManager.h"
#include "Texture.h"
#include "Defines.h"
#include "Camera.h"
#include "Inventory.h"

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
            EntityState = "idle";
            x = X; y = Y;
      }
      
      void Render() {
            tex->Render(EntityState, x - camera.x, y - camera.y);
      }
};


#endif