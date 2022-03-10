#ifndef LIST_CLASS_H
#define LIST_CLASS_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

#include "../ItemManager.h"
#include "../utilities/vector.h"
#include "../utilities/rect.h"
#include "../utilities/MouseClickInRect.h"
#include "../Defines.h"
#include "../Entity.h"
#include "../Inventory.h"
#include "Font.h"
#include "GuiElement.h"

struct InventoryList : public GuiElement
{
      Rectangle rect;
      Inventory* inventory;
      game::font* main_font;
      float mouse_wheel_offset;

      int hovered_element;

      std::string *item_selector;

      InventoryList(Entity *link_entity, Rect _rect, vec2 _pos, game::font* _font) : GuiElement(_pos) {
            rect = {0, 0, _rect.w, _rect.h};
            inventory = link_entity->inventory;
            mouse_wheel_offset = 0;
            main_font = _font;
            hovered_element = -1;
      }

      void BindSelector(std::string *_item_selector) {
            item_selector = _item_selector;
      }

      void Update() {
            float mouseW = 15*GetMouseWheelMove();

            if (mouse_wheel_offset + mouseW <= 0) {
                  mouse_wheel_offset += mouseW;
            }

            for(int y = 0; y < static_cast<int>(inventory->storage.size()); y++) {
                  float x_pos = pos.x + offset.x;
                  float y_pos = pos.y + offset.y + y * 56 + mouse_wheel_offset;
                  if(MauseClickInRect( {150, 50}, {x_pos, y_pos})) {
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                              *item_selector = inventory->storage[y].item.id; 
                        }

                        hovered_element = y; 
                        break; 
                  }
            }
      }

      void Render() {
            BeginScissorMode(pos.x + offset.x, pos.y + offset.y, rect.width, rect.height);        
      
            DrawRectangleV({pos.x + offset.x, pos.y + offset.y}, {rect.width, rect.height}, {150, 150, 150, 150});
            
            for(int y = 0; y < static_cast<int>(inventory->storage.size()); y++) {
                  float x_pos = pos.x + offset.x;
                  float y_pos = pos.y + offset.y + y * 56 + mouse_wheel_offset;

                  if (hovered_element == y) {
                        DrawRectangle(x_pos, y_pos, 150, 50, GRAY);
                  } else {
                        DrawRectangle(x_pos, y_pos, 150, 50, D_LIGHTGREY);
                  }

                  DrawTextEx(*main_font->Rfont, inventory->storage[y].item.id.c_str(), {x_pos, y_pos} , 24, 0, RAYWHITE); 
                  //DrawTextEx(*main_font->Rfont, inventory->storage[y].item.type.c_str(), {x_pos, y_pos + 20} , 15, 0, BLUE); 
                  DrawTextEx(*main_font->Rfont, std::to_string(inventory->storage[y].count).c_str(), {x_pos + 130, y_pos} , 24, 0, RAYWHITE); 
            }
            EndScissorMode();
      }
};

#endif