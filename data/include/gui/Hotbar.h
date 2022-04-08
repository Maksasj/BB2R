#ifndef HOTBAR_CLASS_H
#define HOTBAR_CLASS_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>

#include "../Texture/TextureManager.h"
#include "../Utilities/vector.h"
#include "../Utilities/rect.h"
#include "../Utilities/MouseClickInRect.h"
#include "../Defines.h"
#include "../Player/Player.h"
#include "GuiElement.h"

struct Hotbar : public GuiElement
{   
      int n_cell, a_cell, hover;
      Player *linked_player;
      TextureManager *texturemanager;
      std::vector<std::string> item_id;

      Hotbar(Player *player, int n, vec2 _pos = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}) : GuiElement(_pos) {
            n_cell = n; hover = -1; a_cell = 0;
            linked_player = player;

            for (float x = 0; x < n_cell; x++) {
                  item_id.push_back("nothing");
            }
      }

      void SetUpTextureManager(TextureManager *_texturemanager) {
            texturemanager = _texturemanager;
      }

      void Update() {
            item_id = linked_player->hotbar_item_list;

            for (float x = 0; x < n_cell; x++) {
                  if (linked_player->inventory->GetItemCount(item_id[x]) <= 0) {
                        item_id[x] = "nothing";
                        linked_player->hotbar_item_list[x] = "nothing";
                  } 


                  if(MauseClickInRect({65, 65}, {100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9})) {
                        hover = x;
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                              a_cell = x;
                              linked_player->hotbar_active_cell = a_cell;
                              linked_player->hotbar_item_id = item_id[x];
                        } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) { 
                              linked_player->hotbar_item_id = "nothing";
                              linked_player->hotbar_item_list[x] = "nothing";
                              item_id[x] = "nothing";
                        }
                  }
            }
      }

      void Render() {
            for (float x = 0; x < n_cell; x++) {
                  if (x == a_cell) {
                        DrawRectangleV({100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9 - 5}, {75, 75}, {120, 220, 120, 220} );
                        } else {
                        DrawRectangleV({100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9}, {65, 65}, {180, 180, 180, 150} );
                        if (hover == x) { DrawRectangleLinesEx({100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9, 65, 65}, 3, D_LIGHTGREY); }
                  }

                  //Draw actual item , but before check if it exist in this slot
                  if (item_id[x] != "nothing") { texturemanager->Textures[item_id[x]]->Render("idle", 100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9 - 5); }
            }
      }
};

#endif