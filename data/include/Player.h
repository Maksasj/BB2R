#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>
#include <raylib.h>
#include <map>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <raylib.h> 

#include "Shader.h"
#include "utilities/vector.h"
#include "utilities/key_exist.h"

#include "ItemManager.h"
#include "Hand.h"
#include "Chunk.h"
#include "Entity.h"
#include "Timer.h"
#include "Camera.h"
#include "Defines.h"
#include "Inventory.h"

struct Player : public Entity
{   
      float velocity, speed; vec2 acceleration;
      bool w_pressed, s_pressed, a_pressed, d_pressed;

      std::string hotbar_item_id;
      int hotbar_active_cell;
      std::vector<std::string> hotbar_item_list;

      Hand *hand;
      ItemManager *itemmanager;

      int place_direction;

      Player (TextureManager *texturemanager, float X, float Y) : Entity(texturemanager, "player", X, Y) {
            EntityState = "player_idle";
            velocity = 1.5;
            speed = 20.0;
            acceleration = {0, 0};

            hotbar_item_id = "pickaxe";
            hotbar_active_cell = 0;

            place_direction = 1;

            inventory = new Inventory(5);
            inventory->AddItem("conveyor", 500);
            inventory->AddItem("lamp", 500);

            hotbar_item_list.push_back("pickaxe");
            for (float x = 1; x < 6; x++) {
                  hotbar_item_list.push_back("nothing");
            }
      }

      void SetUpHand(Hand *_hand) {
            hand = _hand;
      }

      void SetUpNEU(ItemManager *_itemmanager) { // Like this NEU mod from minecraft :)
            itemmanager = _itemmanager;
            inventory->SetUpNEU(_itemmanager);
      }

      void Update() {
            if(IsKeyDown(KEY_W)) {  acceleration.y -= speed*timer.deltaTime; EntityState = "player_run_up"; }
            if(IsKeyDown(KEY_S)) {  acceleration.y += speed*timer.deltaTime; EntityState = "player_run_down"; } 
            if(IsKeyDown(KEY_A)) {  acceleration.x -= speed*timer.deltaTime; EntityState = "player_run_left"; }
            if(IsKeyDown(KEY_D)) {  acceleration.x += speed*timer.deltaTime;  EntityState = "player_run_right"; }
            if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) { EntityState = "player_idle"; }

            //Add acceleration to cords, sure with checking collision
            if (hand->TryWalk( {x + acceleration.x, y} )) { x += acceleration.x; }
            if (hand->TryWalk( {x, y + acceleration.y} )) { y += acceleration.y; }

            //Slow down acceleration
            float slipp = hand->GetSlipp(x, y);
            acceleration.x *= slipp;
            acceleration.y *= slipp;

            /* Mouse camera
            float lxO = GetMousePosition().x - (SCREEN_WIDTH/2.0);
            float lyO = GetMousePosition().y - (SCREEN_HEIGHT/2.0);

            lxO *= 0.3;
            lyO *= 0.3;
            */
           
            camera.x = x + 32.0 - (HALF_SCREEN_WIDTH); //+ lxO;
            camera.y = y + 32.0 - (HALF_SCREEN_HEIGHT); //+ lyO;

            //Try use item
            if (key_exists(itemmanager->ItemData, hotbar_item_id)) { 
                  if (itemmanager->ItemData[hotbar_item_id].contains("usage")) { 
                        TryUseItem(); 
                  }
            }

            if(IsKeyPressed(KEY_Q)) {
                  if (hotbar_item_id != "nothing") {
                        hand->TryDropItem(hotbar_item_id, x, y);
                        //inventory->SubtractItem(hotbar_item_id, 1);
                  }
            }
      }

      void TryUseItem() {
            if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                  int item_count = inventory->GetItemCount(hotbar_item_id);

                  if (itemmanager->ItemData[hotbar_item_id]["usage"]["type"] == "place") {
                        if(item_count > 0 && hand->TryPlaceBlock(x, y, hotbar_item_id)) {
                              hand->place_direction = place_direction;
                              hand->PlaceBlock(x, y, hotbar_item_id);
                              inventory->SubtractItem(hotbar_item_id, 1);
                        }
                  } else if (itemmanager->ItemData[hotbar_item_id]["usage"]["type"] == "use") {
                        //Try use item
                  }
            } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                  if (itemmanager->ItemData[hotbar_item_id]["usage"]["type"] == "break") {
                        if(hand->TryBreakBlock(x, y)) {
                              hand->BreakBlock(x, y);
                        }
                  }
            }

            if(IsKeyDown(KEY_F)) {
                  Drop tmp_drop = hand->TryPickUpItem(x, y);
                  if (tmp_drop.item_id != "nothing") { inventory->AddItem(tmp_drop.item_id, tmp_drop.count); }
            }

            if(IsKeyPressed(KEY_R)) {
                  if (place_direction + 1 <= 4) {
                        place_direction++;
                  } else {
                        place_direction = 0;
                  }
            }
      }

      void Render(Shader shader) {
            // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT
            if(place_direction == 1) {
                  DrawText("UP", 100, 100, 50, WHITE);  
            } else if(place_direction == 2) {
                  DrawText("DOWN", 100, 100, 50, WHITE);  
            } else if(place_direction == 3) {
                  DrawText("LEFT", 100, 100, 50, WHITE);  
            } else if(place_direction == 4) {
                  DrawText("RIGHT", 100, 100, 50, WHITE);  
            }

            tex->Render(EntityState, x - camera.x, y - camera.y);
      }
};


#endif