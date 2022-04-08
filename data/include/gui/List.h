#ifndef LIST_CLASS_H
#define LIST_CLASS_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>

#include "../Utilities/vector.h"
#include "../Utilities/rect.h"
#include "../Utilities/MouseClickInRect.h"
#include "../Defines.h"
#include "GuiElement.h"

struct List : public GuiElement
{
      Rectangle rect;

      List(Rect _rect, vec2 _pos) : GuiElement(_pos) {
            rect = {0, 0, _rect.w, _rect.h};
      }

      void Update() {
            
      }

      void Render() {
            BeginScissorMode(pos.x + offset.x, pos.y + offset.y, rect.width, rect.height);        
            
            DrawRectangle(0, 0, 1000, 1000, BLACK);
            DrawRectangleV({pos.x + offset.x, pos.y + offset.y}, {rect.width, rect.height}, {150, 150, 150, 150});
      
            EndScissorMode();

      }
};

#endif