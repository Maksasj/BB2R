#ifndef FIELD_CLASS_H
#define FIELD_CLASS_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>

#include "../utilities/vector.h"
#include "../utilities/rect.h"
#include "../Defines.h"
#include "GuiElement.h"

struct Field : public GuiElement
{   
      Rectangle rect; Color color;
      Field(Rect _rect, vec2 _pos, Color _color) : GuiElement(_pos) {
            rect.width = _rect.w; rect.height = _rect.h;
            color = _color;
      }

      void Render() {
            DrawRectangleV({pos.x + offset.x, pos.y + offset.y}, {rect.width, rect.height}, color);
            
            //DrawRectangleLinesEx({pos.x, pos.y, rect.width, rect.height}, 2, D_LIGHTGREY);
            //DrawRectangleRounded({pos.x, pos.y, rect.width, rect.height}, 25, 8, BLACK); 
      }
};

#endif