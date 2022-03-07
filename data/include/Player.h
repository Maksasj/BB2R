#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <raylib.h>

#include "ItemManager.h"
#include "Hand.h"
#include "Chunk.h"
#include "Block.h"
#include "Entity.h"
#include "Timer.h"
#include "Camera.h"
#include "Defines.h"
#include "Inventory.h"

struct Player : public Entity
{   
      float velocity, speed;
      bool w_pressed, s_pressed, a_pressed, d_pressed;
      int a_hotbar;
      Hand *hand;
      ItemManager *itemmanager;

      Player (TextureManager *texturemanager, float X, float Y) : Entity(texturemanager, "player", X, Y) {
            EntityState = "player_idle";
            velocity = 1.5;
            speed = 640.0;
            a_hotbar = 0;

            inventory = new Inventory(5);
      }

      void SetUpHand(Hand *_hand) {
            hand = _hand;
      }

      void SetUpNEU(ItemManager *_itemmanager) { // Like this NEU mod from minecraft :)
            itemmanager = _itemmanager;
      }

      void Update() {
            if(IsKeyDown(KEY_W)) { y -= speed*timer.deltaTime; EntityState = "player_run_up"; }
            if(IsKeyDown(KEY_S)) { y += speed*timer.deltaTime; EntityState = "player_run_down";} 
            if(IsKeyDown(KEY_A)) { x -= speed*timer.deltaTime; EntityState = "player_run_left"; }
            if(IsKeyDown(KEY_D)) { x += speed*timer.deltaTime; EntityState = "player_run_right"; }
            if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) { EntityState = "player_idle"; }

            /* Mouse camera
            float lxO = GetMousePosition().x - (SCREEN_WIDTH/2.0);
            float lyO = GetMousePosition().y - (SCREEN_HEIGHT/2.0);

            lxO *= 0.3;
            lyO *= 0.3;
            */

            camera.x = x + 32.0 - (SCREEN_WIDTH/2.0); //+ lxO;
            camera.y = y + 32.0 - (SCREEN_HEIGHT/2.0); //+ lyO;

            TryUseItem();
      }

      void TryUseItem() {
            
            if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                  std::string item_id = inventory->storage[a_hotbar].item.id;
                  int item_count = inventory->storage[a_hotbar].count;

                  if (itemmanager->ItemData[item_id]["usage"] == "place") {
                        if(item_count > 0 && hand->TryPlaceBlock(x, y, item_id)) {
                              //DrawText((std::to_string(a_hotbar)+" "+inventory->storage[a_hotbar].item.id+" "+std::to_string(inventory->storage[a_hotbar].count)).c_str(), 100, 300, 36, WHITE);  
                              hand->PlaceBlock(x, y, item_id);
                              inventory->storage[a_hotbar].count -= 1;
                        }
                  } else if (itemmanager->ItemData[item_id]["usage"] == "use") {
                        //Try use item
                  }

            } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                  std::string item_id = inventory->storage[a_hotbar].item.id;

                  if (itemmanager->ItemData[item_id]["usage"] == "break") {
                        if(hand->TryBreakBlock(x, y)) {
                              std::string drop = hand->BreakBlock(x, y);
                              inventory->AddItem(drop, 1);
                        }
                  }
            }
      }

      void Render() {
            tex->Render(EntityState, x - camera.x, y - camera.y);
      }
};


#endif