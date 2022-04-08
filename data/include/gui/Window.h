#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <iostream>
#include <vector>
#include <memory>

#include "../Utilities/vector.h"
#include "../Utilities/rect.h"
#include "../Utilities/MouseClickInRect.h"

#include "Text.h"
#include "GuiElement.h"
#include "Field.h"

struct Window : public Field
{   
      std::vector<std::unique_ptr<GuiElement>> GuiElements;

      bool drag, draggable;
      Rect dzr; // Draggable zone rect
      vec2 dzc; // Draggable zone cords
      vec2 drag_offset; // Mouse drag offset

      bool title;
      Text *title_text;
      Vector2 title_size;

      bool hover;
      bool visible;
      int closing_key;

      Window(Rect _rect, vec2 _pos) : Field(_rect,  _pos, D_GREY) {
            draggable = title = drag = hover = visible = false; closing_key = 0;
      }

      void setDraggable(Rect _rect) {  dzr = _rect; dzc.x = pos.x; dzc.y = pos.y; draggable = true; }
      void SetKey(KeyboardKey key) { closing_key = (int)key; }
      
      void setTitle(std::string _title , game::font* _font) { 
            title_size = MeasureTextEx(*_font->Rfont, _title.c_str(), 20, 0); 
            title_text = new Text(_title, _font, 20, vec2{(dzc.x + dzr.w/2 - title_size.x/2) , (dzc.y + dzr.h/2 - title_size.y/2)});
            title = true;
      }


      void addElement(GuiElement *element, vec2 _offset) { 
            element->offset = _offset; element->pos = pos;
            GuiElements.emplace_back(element); 
      }

      void Update() {
            if (IsKeyPressed(closing_key)) {  if (visible) { visible = false; } else { visible = true; }  }
      
            if (visible) {
                  if(draggable && drag) {
                        pos = {GetMousePosition().x - drag_offset.x, GetMousePosition().y - drag_offset.y};
                        dzc = pos; title_text->pos = {(dzc.x + dzr.w/2 - title_size.x/2) , (dzc.y + dzr.h/2 - title_size.y/2)};
                        for(auto& element : GuiElements) { element->pos = pos; }
                  }

                  if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) { drag = false; }
                  if(MauseClickInRect( {rect.width, rect.height}, pos)) { hover = true; } else { hover = false; }

                  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && MauseClickInRect(dzr, pos)) { 
                        drag = true; drag_offset = {GetMousePosition().x - pos.x, GetMousePosition().y - pos.y};
                  }

                  for(auto& element : GuiElements) { element->Update(); }
            }
      }

      void Render() {
            if (visible) {
                  //Rendering Windows it self
                  DrawRectangleV({pos.x, pos.y}, {rect.width, rect.height}, color);

                  if(draggable) { DrawRectangleV({dzc.x, dzc.y}, {dzr.w, dzr.h}, GRAY); } 
                  if(title) { title_text->Render(); }
                  if (hover) { DrawRectangleLinesEx({pos.x, pos.y, rect.width, rect.height}, 2, D_LIGHTGREY); }

                  //Rendering SubElements
                  for(auto& element : GuiElements) { element->Render(); }
            }
      }
};

#endif