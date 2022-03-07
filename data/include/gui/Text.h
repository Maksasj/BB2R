#ifndef TEXT_CLASS_H
#define TEXT_CLASS_H

#include <iostream>
#include <stdio.h>

#include "../utilities/vector.h"
#include "Font.h"
#include "GuiElement.h"

struct Text : public GuiElement
{   
      game::font *Gfont;
      std::string actext;
      float font_size;

      Text(std::string _text, game::font* _font, float _font_size,  vec2 _pos) : GuiElement(_pos) {
            Gfont = _font;
            actext = _text;
            font_size = _font_size;
      }

      void Render() {
            DrawTextEx(*Gfont->Rfont, actext.c_str(), {pos.x + offset.x, pos.y + offset.y} , font_size, 0, RAYWHITE); 
      }
};

#endif