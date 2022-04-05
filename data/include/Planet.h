#ifndef PLANET_CLASS_H
#define PLANET_CLASS_H

#include <iostream>
#include <raylib.h>
#include <stdio.h>
#include <cmath>

#include "Shader.h"
#include "World.h"
#include "Player.h"
#include "TextureManager.h"
#include "ModLoader.h"
#include "Timer.h"

struct Planet
{   
      World *world;
      float ambient_light;
      float ambient_light_min = 0.2;
      float day_lenght = 1600.0;

      Planet(TextureManager *texturemanager, ModLoader *modloader) {
            world = new World(texturemanager, modloader, "clear_earth");
            ambient_light = 0;
      }

      void Update(Player *player) {

            world->Update(player->x, player->y);

            ambient_light = ((sin(timer.step/day_lenght) + 1)/2.0) + ambient_light_min;
      }

      void GetLight(LightSystem *lightsystem, Player *player) {
            world->GetLight(lightsystem, player->x, player->y);
      }

      void Render(Shader shader, Player* player) {
            world->Render(shader, player->x , player->y);
      }

};

#endif