#ifndef LIST_CLASS_H
#define LIST_CLASS_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

#include "../Mod/ItemManager.h"
#include "../Utilities/vector.h"
#include "../Utilities/rect.h"
#include "../Utilities/MouseClickInRect.h"
#include "../Defines.h"
#include "../prototype/Entity.h"
#include "../Player/Inventory.h"
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

                  
                  DrawTextEx(*main_font->Rfont, ((std::string)inventory->itemmanager->ItemData[inventory->storage[y].item.id]["title"]).c_str(), {x_pos + 2, y_pos} , 24, 0, RAYWHITE); 
                  
                  if (inventory->itemmanager->ItemData[inventory->storage[y].item.id]["tags"]["type"].contains("title")) {
                        std::string _tmp_text = inventory->itemmanager->ItemData[inventory->storage[y].item.id]["tags"]["type"]["title"];
                        Color _color = {255, 255, 255, 255};

                        //Check if item have color value for type
                        if(inventory->itemmanager->ItemData[inventory->storage[y].item.id]["tags"]["type"].contains("color")) {  _color = { inventory->itemmanager->ItemData[inventory->storage[y].item.id]["tags"]["type"]["color"][0], inventory->itemmanager->ItemData[inventory->storage[y].item.id]["tags"]["type"]["color"][1], inventory->itemmanager->ItemData[inventory->storage[y].item.id]["tags"]["type"]["color"][2], 255 }; }
                        
                        Vector2 title_size = MeasureTextEx(*main_font->Rfont, _tmp_text.c_str(), 20, 0); 
                        DrawTextEx(*main_font->Rfont, _tmp_text.c_str(), {x_pos + 2, y_pos + 50 - title_size.y} , 20, 0, _color); 
                  }

                  Vector2 count_text_size = MeasureTextEx(*main_font->Rfont, std::to_string(inventory->storage[y].count).c_str(), 24, 0); 
                  DrawTextEx(*main_font->Rfont, std::to_string(inventory->storage[y].count).c_str(), {x_pos + 150 - count_text_size.x - 3, y_pos} , 24, 0, RAYWHITE); 
                  
                  Vector2 max_stack_text_size = MeasureTextEx(*main_font->Rfont, std::to_string((int)inventory->itemmanager->ItemData[inventory->storage[y].item.id]["stack_size"]).c_str(), 24, 0); 
                  DrawTextEx(*main_font->Rfont, std::to_string((int)inventory->itemmanager->ItemData[inventory->storage[y].item.id]["stack_size"]).c_str(), {x_pos + 150 - max_stack_text_size.x - 3, y_pos + 50 - max_stack_text_size.y} , 24, 0, {153, 153, 153, 255}); 
                  
            }
            EndScissorMode();
      }
};

#endif