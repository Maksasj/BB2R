#ifndef HOTBAR_CLASS_H
#define HOTBAR_CLASS_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>

#include "../TextureManager.h"
#include "../utilities/vector.h"
#include "../utilities/rect.h"
#include "../utilities/MouseClickInRect.h"
#include "../Defines.h"
#include "../Player.h"
#include "GuiElement.h"

struct Hotbar : public GuiElement
{   
      int n_cell, a_cell, hover;
      Player *linked_player;
      TextureManager *texturemanager;

      Hotbar(Player *player, int n, vec2 _pos = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}) : GuiElement(_pos) {
            n_cell = n; hover = -1; a_cell = 0;
            linked_player = player;
      }

      void SetUpTextureManager(TextureManager *_texturemanager) {
            texturemanager = _texturemanager;
      }

      void Update() {
            for (float x = 0; x < n_cell; x++) {
                  if(MauseClickInRect({65, 65}, {100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9})) {
                        hover = x;
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { a_cell = x; linked_player->a_hotbar = x;}
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
                  if (x < static_cast<int>(linked_player->inventory->storage.size())) {
                        texturemanager->Textures[linked_player->inventory->storage[x].item.id]->Render("idle", 100 * x + SCREEN_WIDTH/2 - (50 * n_cell), SCREEN_HEIGHT * 0.9 - 5);
                  }
            }
      }
};

#endif