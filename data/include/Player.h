#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <raylib.h> 

#include "utilities/vector.h"

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

      vec2 acceleration;


      Player (TextureManager *texturemanager, float X, float Y) : Entity(texturemanager, "player", X, Y) {
            EntityState = "player_idle";
            velocity = 1.5;
            speed = 20.0;
            a_hotbar = 0;

            acceleration = {0, 0};

            inventory = new Inventory(5);
      }

      void SetUpHand(Hand *_hand) {
            hand = _hand;
      }

      void SetUpNEU(ItemManager *_itemmanager) { // Like this NEU mod from minecraft :)
            itemmanager = _itemmanager;
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
            if (itemmanager->ItemData[inventory->storage[a_hotbar].item.id].contains("usage")) { TryUseItem(); }
      }

      void TryUseItem() {
            if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            std::string item_id = inventory->storage[a_hotbar].item.id;
            int item_count = inventory->storage[a_hotbar].count;

            if (itemmanager->ItemData[item_id]["usage"]["type"] == "place") {
                  if(item_count > 0 && hand->TryPlaceBlock(x, y, item_id)) {
                        hand->PlaceBlock(x, y, item_id);
                        inventory->storage[a_hotbar].count -= 1;
                        inventory->SortInStacks();
                  }
            } else if (itemmanager->ItemData[item_id]["usage"]["type"] == "use") {
                  //Try use item
            }

            } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                  std::string item_id = inventory->storage[a_hotbar].item.id;

                  if (itemmanager->ItemData[item_id]["usage"]["type"] == "break") {
                        if(hand->TryBreakBlock(x, y)) {
                              Drop tmp_drop = hand->BreakBlock(x, y);
                              if (tmp_drop.item_id != "nothing") { inventory->AddItem(tmp_drop.item_id, tmp_drop.count); }
                        }
                  }
            }
      }

      void Render() {
            tex->Render(EntityState, x - camera.x, y - camera.y);
      }
};


#endif